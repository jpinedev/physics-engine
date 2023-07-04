#include <stdexcept>

#include "core/Engine.hpp"
#include "core/GameObject.hpp"
#include "core/RenderContext.hpp"
#include "core/TransformComponent.hpp"
#include "core/UpdateContext.hpp"
#include "core/collision/ColliderComponent.hpp"

#ifdef GIZMOS
#include "core/util/Gizmos.hpp"
#endif

GameObject::GameObject(Engine* engine) : mEngine(engine)
{
    mTransform = new TransformComponent();
}
GameObject::GameObject(GameObject&& from) noexcept
{
    mEngine = from.mEngine;
    from.mEngine = nullptr;
    mTransform = from.mTransform;
    from.mTransform = nullptr;
    mComponents = std::move(from.mComponents);
    for (Component* component : mComponents)
    {
        component->mGameObject = this;
    }
}

GameObject::~GameObject()
{
    for (Component* pC : mComponents)
    {
        delete pC;
    }

    if (mTransform)
    {
        delete mTransform;
    }
}

void GameObject::Start()
{
    for (Component* component : mComponents)
    {
        component->Start();
    }
}

void GameObject::Update(UpdateContext* update)
{
    for (Component* component : mComponents)
    {
        component->Update(update);
    }
}

void GameObject::Render(RenderContext* renderer)
{
    for (Component* component : mComponents)
    {
        component->Render(renderer);
    }
}

#ifdef GIZMOS
void GameObject::DrawGizmos(RenderContext* renderer, util::Gizmos* gizmos)
{
    for (Component* component : mComponents)
    {
        component->DrawGizmos(renderer, gizmos);
    }
}
#endif

bool GameObject::IsColliding(ColliderComponent* other, FRect* rectangle)
{
    ColliderComponent* collider = (ColliderComponent*)GetComponent("collider");
    // Game object does not have a collider
    if (!collider) return false;

    // Checking collision with self
    if (collider == other) return false;

    return collider->CheckCollisionWithRectangle(rectangle);
}

bool GameObject::RaycastCollider(ColliderComponent* collider, FRect* rectangle)
{
    return mEngine->IsColliding(collider, rectangle);
}

void GameObject::AddComponent(Component* toAdd)
{
    if (toAdd->mGameObject != nullptr)
    {
        throw std::invalid_argument(
            "You cannot add the same component to more than one game object. "
            "If you want to switch ownership, then first remove it from the "
            "other game object.");
    }

    // Ensure that the component does not already exist
    for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        if ((*it)->GetType() == toAdd->GetType())
        {
            throw std::invalid_argument(
                "You cannot add a component that already exists.");
        }
    }

    mComponents.push_back(toAdd);
    toAdd->mGameObject = this;
}

void GameObject::RemoveComponent(const std::string& typeName)
{
    for (auto it = mComponents.begin(); it != mComponents.end();)
    {
        if ((*it)->GetType() == typeName)
        {
            (*it)->mGameObject = nullptr;
            it = mComponents.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

Component* GameObject::GetComponent(const std::string& typeName)
{
    for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        if ((*it)->GetType() == typeName)
        {
            return *it;
        }
    }

    return nullptr;
}

TransformComponent& GameObject::GetTransform() { return *mTransform; }

void GameObject::BroadcastMessage(const std::string& message) const
{
    for (Component* c : mComponents)
    {
        c->Receive(message);
    }
}
