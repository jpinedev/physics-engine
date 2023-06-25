#include "core/TransformComponent.hpp"

TransformComponent::TransformComponent()
    : Component("transform"), mPosition(0, 0)
{
}

TransformComponent::~TransformComponent() {}

// Returns the position of this transform
Vec2D TransformComponent::GetPosition() const { return mPosition; }

// Sets the x and y position of this transform
void TransformComponent::SetPosition(float x, float y)
{
    mPosition.x = x;
    mPosition.y = y;
}

// Translates the x and y position of this transform
void TransformComponent::TranslatePosition(float x, float y)
{
    mPosition.x += x;
    mPosition.y += y;
}
