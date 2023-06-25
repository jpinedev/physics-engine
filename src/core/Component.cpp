#include "core/Component.hpp"
#include "core/GameObject.hpp"
#include "core/RenderContext.hpp"
#include "core/UpdateContext.hpp"

Component::Component(std::string type) { mType = type; }
Component::~Component() {}

void Component::Receive(const std::string& message) {}

std::string Component::GetType() const { return mType; }

void Component::Update(UpdateContext* update) {}

void Component::Render(RenderContext* renderer) {}
