#include "core/collision/ColliderComponent.hpp"

#include <iostream>

ColliderComponent::ColliderComponent() : Component("collider") {}

bool ColliderComponent::CheckCollisionWithRectangle(SDL_Rect* rect)
{
    bool collides = CollidesWithRectangle(rect);

    if (collides && mIsTrigger)
    {
        mGameObject->BroadcastMessage("trigger_collided");
    }

    return !mIsTrigger && collides;
}

void ColliderComponent::SetIsTrigger(bool isTrigger) { mIsTrigger = isTrigger; }
