#include "core/ControllerComponent.hpp"
#include "core/GameObject.hpp"
#include "core/InputManager.hpp"
#include "core/TransformComponent.hpp"
#include "core/UpdateContext.hpp"
#include "core/collision/ColliderComponent.hpp"

#include <cinttypes>
#include <glm/vec2.hpp>
#include <iostream>

ControllerComponent::ControllerComponent() : Component("controller") {}

ControllerComponent::~ControllerComponent() {}

void ControllerComponent::Update(UpdateContext* update)
{
    TransformComponent& transform = mGameObject->GetTransform();

    int horizontal = InputManager::State->GetAxis("D", "A");
    int vertical = -InputManager::State->GetAxis("W", "S");

    if (horizontal == 0 && vertical == 0)
    {
        // idle
        mGameObject->BroadcastMessage("idle");
        update->cameraCenter = transform.GetPosition();
        return;
    }

    if (horizontal == 1)
    {
        // moving right
        mGameObject->BroadcastMessage("move_right");
    }
    else if (horizontal == -1)
    {
        // moving left
        mGameObject->BroadcastMessage("move_left");
    }
    else if (vertical == 1)
    {
        // moving down
        mGameObject->BroadcastMessage("move_down");
    }
    else if (vertical == -1)
    {
        // moving up
        mGameObject->BroadcastMessage("move_up");
    }

    glm::vec2 move(horizontal, vertical);
    move = glm::normalize(move);
    move *= mMoveSpeed * update->deltaTime;
    transform.TranslatePosition(move.x, move.y);

    ColliderComponent* collider =
        (ColliderComponent*)mGameObject->GetComponent("collider");

    // move gameobject back if collides
    if (collider)
    {
        if (collider->RaycastColliderRectangle())
            transform.TranslatePosition(-move.x, -move.y);
    }

    update->cameraCenter = transform.GetPosition();
}

void ControllerComponent::SetSpeed(float val) { mMoveSpeed = val; }
