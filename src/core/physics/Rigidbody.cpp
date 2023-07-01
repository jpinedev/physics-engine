#include "core/physics/Rigidbody.hpp"
#include "core/TransformComponent.hpp"

namespace Physics
{

Rigidbody::Rigidbody() : Component("rigidbody") {}
Rigidbody::~Rigidbody() {}

void Rigidbody::Start() { mPos = mGameObject->GetTransform().GetPosition(); }

}  // namespace Physics
