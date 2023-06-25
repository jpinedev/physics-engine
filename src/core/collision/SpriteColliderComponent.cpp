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

bool SpriteColliderComponent::CollidesWithRectangle(SDL_Rect* rect)
{
    FindSpriteRendererIfNull();

    SDL_Rect colliderRect = GetCollisionRect();

    return (SDL_HasIntersection(&colliderRect, rect) == SDL_TRUE);
}

bool SpriteColliderComponent::RaycastColliderRectangle()
{
    SDL_Rect colliderRect = GetCollisionRect();

    return mGameObject->RaycastCollider(dynamic_cast<ColliderComponent*>(this),
                                        &colliderRect);
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

SDL_Rect SpriteColliderComponent::GetCollisionRect()
{
    FindSpriteRendererIfNull();

    Vec2D position = mGameObject->GetTransform().GetPosition();

    SDL_Rect colliderRect = mSpriteRenderer->GetDisplayDimensions();
    colliderRect.x = (int)position.x;
    colliderRect.y = (int)position.y;

    return colliderRect;
}
