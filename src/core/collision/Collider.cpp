#include "core/GameObject.hpp"
#include "core/collision/ColliderComponent.hpp"

#include <iostream>

ColliderComponent::ColliderComponent() : Component("collider") {}

bool ColliderComponent::CheckCollisionWithRectangle(FRect* rect)
{
    bool collides = CollidesWithRectangle(rect);

    if (collides && mIsTrigger)
    {
        mGameObject->BroadcastMessage("trigger_collided");
    }

    return !mIsTrigger && collides;
}
