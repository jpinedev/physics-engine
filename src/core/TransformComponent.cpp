#include "core/TransformComponent.hpp"

TransformComponent::TransformComponent()
    : Component("transform"), mPosition(0, 0)
{
}

TransformComponent::~TransformComponent() {}
