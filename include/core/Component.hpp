#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

#include <string>

#include "core/GameObject.hpp"
#include "core/RenderContext.hpp"
#include "core/UpdateContext.hpp"

#ifdef GIZMOS
#include "core/util/Gizmos.hpp"
#endif

/**
 * An abstract base class for all components.
 *
 * A Component must be attached to a GameObject.
 * WARN: Do not manually instantiate a component via a constructor.
 *   Always create a component using Engine's InstantiateComponent<T> method.
 *
 * WARN: when creating a new component, always write a virtual destructor,
 *   and mark override any desired virtual life cycle functions.
 *
 * TODO: add ability to enable and disable components
 */
class Component
{
public:
    // Component();
    /**
     * A constructor that is not allowed to be implemented
     */
    Component() = delete;
    /**
     * A destructor
     */
    virtual ~Component() {}

    /**
     * Receives the given message for this to consider
     * @param message The message recieved
     */
    virtual void Receive(const std::string& message) {}

    /**
     * Returns a copy of this name
     * @return The name of this component
     */
    std::string GetType() const { return mType; }

    /**
     * An startup lifecycle event for a component
     */
    virtual void Start() {}

    /**
     * An update loop for a component
     * @param update The update data that operates the update loop
     */
    virtual void Update(UpdateContext* update) {}

    /**
     * A render loop for a component
     * @param renderer The render data that operates the render loop
     */
    virtual void Render(RenderContext* renderer) {}

#ifdef GIZMOS
    virtual void DrawGizmos(RenderContext* renderer, util::Gizmos* util) {}
#endif

    // Allow GameObject to tell the component which game object it is attached
    // to.
    /**
     * Adds a component to the GameObject attached
     * @param component The component added
     */
    friend void GameObject::AddComponent(Component* component);

    /**
     * Removes a component to the GameObject attached
     * @param toRemove The component removed
     */
    friend void GameObject::RemoveComponent(const std::string& toRemove);

    /**
     * Gets the GameObject
     */
    friend GameObject::GameObject(GameObject&&) noexcept;

private:
    /**
     * The type of the component.
     */
    std::string mType;

protected:
    /**
     * Make the class abstract by hiding all constructors as protected.
     */
    Component(std::string type) : mType(type) {}

    /**
     * The game object that this component is attached to.
     *
     * WARN: Should only be modified by the container GameObject.
     */
    GameObject* mGameObject = nullptr;
};

#endif
