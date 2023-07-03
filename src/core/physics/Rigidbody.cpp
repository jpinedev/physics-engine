#include "core/physics/Rigidbody.hpp"
#include "core/GameObject.hpp"
#include "core/collision/ColliderComponent.hpp"
#include "core/TransformComponent.hpp"
#include "core/physics/PhysicsEngine.hpp"
#include "core/Engine.hpp"
#include "core/physics/PhysicsUpdateContext.hpp"

#include <cassert>

namespace Physics
{

Rigidbody::Rigidbody(bool isStatic)
    : Component("rigidbody"), mbIsStatic(isStatic)
{
}
Rigidbody::~Rigidbody() {}

void Rigidbody::Start() {
    mPos = mGameObject->GetTransform().GetPosition();

    mpPhysicsEngine = PhysicsEngine::Instance();
    assert(mpPhysicsEngine);

    ColliderComponent* collider = (ColliderComponent*)mGameObject->GetComponent("collider");

    if (mbIsStatic) {
        std::vector<Bounds> bounds;
        collider->GetBoundingBoxes(bounds);
        mpPhysicsEngine->AddStaticColliders(this, bounds);
        return;
    }

    mpPhysicsEngine->AddDynamicBody(this);
}

void Rigidbody::Update(UpdateContext* ctx)
{
    mGameObject->GetTransform().SetPosition(mPos);
}

void Rigidbody::FixedUpdate(PhysicsUpdateContext* ctx)
{
    if (mbIsStatic) return;

    mVel += ctx->gravity * ctx->kFixedTimestep;
    mPos += mVel * ctx->kFixedTimestep;
}

void Rigidbody::ResolveCollisions(const std::vector<Hit2D>& collisions)
{

}

Bounds Rigidbody::GetBoundingBox() const
{

}

}  // namespace Physics
