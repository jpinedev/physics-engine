#include "core/physics/Rigidbody.hpp"
#include "core/Engine.hpp"
#include "core/GameObject.hpp"
#include "core/TransformComponent.hpp"
#include "core/collision/ColliderComponent.hpp"
#include "core/physics/PhysicsEngine.hpp"
#include "core/physics/PhysicsUpdateContext.hpp"
#include "core/util/SDLConversions.hpp"

#include <cassert>
#include <stdexcept>

namespace Physics
{

Rigidbody::Rigidbody(bool isStatic)
    : Component("rigidbody"), mbIsStatic(isStatic)
{
}
Rigidbody::~Rigidbody() {}

void Rigidbody::Start()
{
    mpTransform = &mGameObject->GetTransform();
    mPos = mpTransform->GetPosition();

    mpPhysicsEngine = PhysicsEngine::Instance();
    if (!mpPhysicsEngine)
        throw std::runtime_error(
            "Physics Engine has not been properly initialized.");

    mpCollider = (ColliderComponent*)mGameObject->GetComponent("collider");

    if (!mpCollider)
        throw std::runtime_error(
            "Rigidbody does not have a Collider component.");

    std::vector<Bounds> allBounds;
    mpCollider->GetBoundingBoxes(allBounds);

    CalculateLocalBounds(allBounds);
    CalculateLocalCenterOfMass();

    if (mbIsStatic)
    {
        mpPhysicsEngine->AddStaticColliders(this, allBounds);
        return;
    }

    mpPhysicsEngine->AddDynamicBody(this);
}

void Rigidbody::Update(UpdateContext* ctx) { mpTransform->SetPosition(mPos); }

void Rigidbody::FixedUpdate(PhysicsUpdateContext const* ctx)
{
    if (mbIsStatic) return;

    mPos += mVel * ctx->kFixedTimestep;
    mVel += ctx->gravity * ctx->kFixedTimestep;
}

void Rigidbody::ResolveCollisions(const std::vector<Hit2D>& collisions)
{
    glm::vec2 netCollision{0, 0};
    bool stopLeftVel, stopRightVel, stopUpVel, stopDownVel;

    glm::vec2 centerOfMass = GetCenterOfMass();
    Bounds bounds = GetBoundingBox();

    for (auto collIt = collisions.begin(), collItEnd = collisions.end();
         collIt != collItEnd; ++collIt)
    {
        const Bounds& overlap = collIt->bounds;
        bool bCollidedLeft = overlap.min.x == bounds.min.x;
        bool bCollidedTop = overlap.min.y == bounds.min.y;
        bool bCollidedRight = overlap.max.x == bounds.max.x;
        bool bCollidedBottom = overlap.max.y == bounds.max.y;

        // If a collision occurs over a whole side, it will only affect
        // the normal axis of that side.
        bool bCollidedHorizontal = bCollidedLeft != bCollidedRight;
        bool bCollidedVertical = bCollidedTop != bCollidedBottom;

        if (bCollidedHorizontal)
        {
            float collisionDist = overlap.right - overlap.left;
            if (bCollidedLeft)
            {
                stopLeftVel = true;
                netCollision.x += collisionDist;
            }
            else
            {
                stopRightVel = true;
                netCollision.x -= collisionDist;
            }
        }

        if (bCollidedVertical)
        {
            float collisionDist = overlap.bottom - overlap.top;
            if (bCollidedTop)
            {
                stopUpVel = true;
                netCollision.y += collisionDist;
            }
            else
            {
                stopDownVel = true;
                netCollision.y -= collisionDist;
            }
        }
    }

    if ((stopLeftVel && mVel.x < 0) || (stopRightVel && mVel.x > 0)) mVel.x = 0;
    if ((stopUpVel && mVel.y < 0) || (stopDownVel && mVel.y > 0)) mVel.y = 0;

    mPos += netCollision;
}

Bounds Rigidbody::GetBoundingBox() const
{
    FRect rect = mLocalBoundsRect;
    rect.pos += mPos;
    return rect;
}

void Rigidbody::CalculateLocalBounds(const std::vector<Bounds>& allBounds)
{
    Bounds bounds = allBounds.front();
    for (auto &boundsIt = ++allBounds.begin(), boundsItEnd = allBounds.end();
         boundsIt != boundsItEnd; ++boundsIt)
    {
        bounds.Union(*boundsIt);
    }

    mLocalBoundsRect = bounds.ToFRect();
    mLocalBoundsRect.pos -= mPos;
}

void Rigidbody::CalculateLocalCenterOfMass()
{
    mLocalCenterOfMass.x = (mLocalBoundsRect.x + mLocalBoundsRect.w) * 0.5f;
    mLocalCenterOfMass.y = (mLocalBoundsRect.y + mLocalBoundsRect.h) * 0.5f;
}

}  // namespace Physics
