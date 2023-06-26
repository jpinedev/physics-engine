#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "core/GameObject.hpp"
#include "core/IGraphicsEngineRenderer.hpp"
#include "core/InputManager.hpp"
#include "core/TinyMath.hpp"
#include "core/UpdateContext.hpp"

/**
 * This class sets up the main game engine and all necessary subsystems.
 */
class Engine
{
public:
    Engine();
    ~Engine();

    void Input(bool* quit);

    /**
     * Per frame update
     * @param update The update data that operates the update loop
     */
    void Update();
    /**
     * Per frame render. Renders everything
     */
    void Render();

    /**
     * Checks if component is colliding with another component
     * @param collider The first component we are checking
     * @param rectangle The second component we are checking
     * @return If the two components collided
     */
    bool IsColliding(ColliderComponent* collider, SDL_Rect* rectangle);

    void RunGameLoop();

    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Startup' to launch the engine
     */
    void Startup();
    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();

    /**
     * Request to startup the Graphics Subsystem
     */
    void InitializeGraphicsSubSystem();

    /**
     * Request to startup the User Input System
     */
    InputState* InitializeInputSystem();

    /**
     * Create a new game object and place it in the scene.
     * See mGameObjects for note about rendering.
     * @return The new game object created
     */
    GameObject& InstantiateGameObject();

    /**
     * Create a new component and attach it to an object.
     * See mGameObjects for note about rendering.
     * @tparam Component_t The type of the component
     * @param obj The game object the component will be attached to
     * @return The new component created
     */
    template <typename Component_t, typename... Args>
    Component_t* InstantiateComponent(GameObject& obj, Args... args)
    {
        // This template method must be defined in the header to be used
        // elsewhere.
        Component* component = (Component*)new Component_t(args...);
        obj.AddComponent(component);
        return (Component_t*)component;
    }

private:
    // Engine Subsystem
    SDLGraphicsEngineRenderer* mRenderer = nullptr;
    // Input management system
    InputManager* mInput = nullptr;

    UpdateContext mUpdateCtx;
    RenderContext mRenderCtx;
#ifdef GIZMOS
    util::Gizmos mGizmosUtil{};
#endif

    Vec2D mScreenSize;
    Vec2D mScreenCenter;

    /**
     * Our scene of game objects.
     * The order of elements determines the order of rendering.
     * Game objects (and their components) are rendered from first to last.
     * Later elements will render above earlier elements.
     */
    std::vector<GameObject*> mGameObjects;
};

#endif  // __ENGINE_HPP__
