#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <optional>
#include <string>
#include <vector>

#include "core/RenderContext.hpp"
#include "core/UpdateContext.hpp"

#ifdef GIZMOS
#include "core/util/Gizmos.hpp"
#endif

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

// Forward declaration to prevent circular dependancies
class Engine;
class Component;
class TransformComponent;
class ColliderComponent;

/**
 * A game object that exists in a scene.
 * Life cycle events triggered on game objects will trigger on its components.
 *
 * All game objects have a transform component (whether or not they need it).
 *
 * TODO: add ability to add children game objects
 * TODO: add Start lifecycle event;
 */
class GameObject final
{
public:
    /**
     * A constructor
     * @param engine The engine we are using
     */
    GameObject(Engine* engine);
    // Must implement Move (noexcept) Contructor to prevent destructor calls on
    // contained components
    /**
     * Moves the resources owned by this game object to another game object
     */
    GameObject(GameObject&&) noexcept;
    /**
     * A destructor
     */
    ~GameObject();

    /**
     * Life cycle event to update the game object and its components every frame
     * @param update The update data that operates the update loop
     */
    void Update(UpdateContext* update);

    /**
     * Life cycle event to render the game object and its components every frame
     * @param renderer The render data that operates the render loop
     */
    void Render(RenderContext* renderer);

#ifdef GIZMOS
    void DrawGizmos(RenderContext* renderer, util::Gizmos* util);
#endif

    /**
     * Checks if any components in this object collides with the rect
     * @param collider The first component we are checking
     * @param rectangle The second component we are checking
     * @return If the two components collided
     */
    bool IsColliding(ColliderComponent* collider, FRect* rectangle);

    /**
     * Checks if component is colliding with another component
     * @param collider The first component we are checking
     * @param rect The second component we are checking
     * @return If the two components collided
     */
    bool RaycastCollider(ColliderComponent* collider, FRect* rect);

    /**
     * Adds the the given component to this game object.
     * Tells the component which game object they are attached to.
     * @param to_add The component we are adding
     */
    void AddComponent(Component* to_add);

    /**
     * Removes and destroys the component of the given type (if it exists on
     * this game object). WARN: removing a component to reattach elsewhere is
     * not currently supported. WARN: removing a component will rearrange the
     * array and will kill existing references.
     * @param type_to_remove The component we are trying to remove
     */
    void RemoveComponent(const std::string& type_to_remove);

    /**
     * Returns the component of the given type, if it exists
     * @param type The type of the component
     * @return The component that we want
     */
    Component* GetComponent(const std::string& type);
    TransformComponent& GetTransform();

    /**
     * Broadcasts the given message to all of this components
     * @param message The message we are trying to broadcast
     */
    void BroadcastMessage(const std::string& message) const;

    bool IsActive() const { return mIsActive; }
    void SetActive(bool isActive) { mIsActive = isActive; }

private:
    Engine* mEngine;
    bool mIsActive = true;
    TransformComponent* mTransform;
    std::vector<Component*> mComponents;
};

#endif
