#include "core/ControllerComponent.hpp"
#include "core/GameObject.hpp"
#include "core/InputManager.hpp"
#include "core/TransformComponent.hpp"
#include "core/UpdateContext.hpp"
#include "core/collision/ColliderComponent.hpp"
#include "core/physics/Rigidbody.hpp"

#include <cinttypes>
#include <glm/vec2.hpp>
#include <iostream>
#include <stdexcept>

ControllerComponent::ControllerComponent() : Component("controller") {}

ControllerComponent::~ControllerComponent() {}

void ControllerComponent::Start()
{
    mpRigidbody = (Physics::Rigidbody*)mGameObject->GetComponent("rigidbody");
    if (!mpRigidbody)
        throw std::runtime_error(
            "ControllerComponent does not have a Rigidbody.");
}

void ControllerComponent::Update(UpdateContext* update)
{
    int horizontal = InputManager::State->GetAxis("D", "A");
    int vertical = -InputManager::State->GetAxis("W", "S");

    // TODO: Extract camera follow code to separate component.
    update->cameraCenter = mpRigidbody->GetPosition();

    if (horizontal == 0 && vertical == 0)
    {
        // idle
        mGameObject->BroadcastMessage("idle");
        mpRigidbody->SetVelocity({0, 0});
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

    glm::vec2 move{horizontal, vertical};
    move = glm::normalize(move);

    mpRigidbody->SetVelocity(move * mMoveSpeed);
}

void ControllerComponent::SetSpeed(float val) { mMoveSpeed = val; }
