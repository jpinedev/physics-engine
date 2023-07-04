#include "core/collision/SpriteColliderComponent.hpp"
#include "core/SpriteRenderer.hpp"

#include <stdexcept>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

SpriteColliderComponent::SpriteColliderComponent() : ColliderComponent() {}
SpriteColliderComponent::~SpriteColliderComponent() {}

bool SpriteColliderComponent::CollidesWithRectangle(FRect* rect)
{
    FindSpriteRendererIfNull();

    return HasIntersection(GetCollisionRect(), *rect);
}

bool SpriteColliderComponent::RaycastColliderRectangle()
{
    FRect colliderRect = GetCollisionRect();

    return mGameObject->RaycastCollider(dynamic_cast<ColliderComponent*>(this),
                                        &colliderRect);
}

void SpriteColliderComponent::GetBoundingBoxes(std::vector<Bounds>& out_bounds)
{
    FRect colliderRect = GetCollisionRect();
    out_bounds.emplace_back(colliderRect);
}

void SpriteColliderComponent::FindSpriteRendererIfNull()
{
    if (mSpriteRenderer) return;

    mSpriteRenderer = (SpriteRenderer*)mGameObject->GetComponent("sprite");

    if (!mSpriteRenderer)
    {
        throw std::runtime_error(
            "SpriteCollider could not find a SpriteRenderer on its game "
            "object.");
    }
}

FRect SpriteColliderComponent::GetCollisionRect()
{
    FindSpriteRendererIfNull();

    return {mGameObject->GetTransform().GetPosition(),
            mSpriteRenderer->GetSize()};
}

#ifdef GIZMOS
void SpriteColliderComponent::DrawGizmos(RenderContext* renderer,
                                         util::Gizmos* util)
{
    util->SetDrawMode(util::Gizmos::DrawMode::DM_STROKE);
    util->SetStrokeColor({0, 0xFF, 0, 0xFF});

    SDL_Rect collisionRect = GetCollisionRect();
    util->DrawRect(renderer->WorldToCamera(collisionRect));
}
#endif
