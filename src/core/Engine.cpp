#include "core/Engine.hpp"
#include "core/Component.hpp"
#include "core/GameObject.hpp"
#include "core/IGraphicsEngineRenderer.hpp"
#include "core/InputManager.hpp"
#include "core/RenderContext.hpp"
#include "core/ResourceManager.hpp"
#include "core/UpdateContext.hpp"

#include <iterator>
#include <map>
#include <memory>
#include <string>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine() {}

// Proper shutdown and destroy initialized objects
Engine::~Engine() {}

// Return Input
void Engine::Input(bool* quit)
{
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if (e.type == SDL_QUIT)
            *quit = true;
        else if (mInput)
            mInput->HandleEvent(e);
    }
}

void Engine::Update()
{
    for (GameObject* pGO : mGameObjects)
    {
        if (!pGO->IsActive()) continue;
        pGO->Update(&mUpdateCtx);
    }
}

void Engine::Render()
{
    // Set the color of the empty framebuffer
    mRenderer->SetRenderDrawColor(0, 0, 0, 0xFF);
    // Clear the screen to the color of the empty framebuffer
    mRenderer->RenderClear();

    // NOTE: We have to dynamic_cast here, because we do not exactly know the
    // type
    //       of the renderer that is going to 'render' our character.
    //       Polymorphism is being used for our renderer, and we need to thus
    //       determine using dynamic_cast if we can make a successful cast to
    //       find a matching member function that can retrieve a 'renderer'
    //       suitable.
    // NOTE: The very fact that I am storing an SDL_Renderer* below completely
    //       defeats the purpose of using the dynamic_cast.
    //       The whole point of the dynamic_cast is so that at run-time we can
    //       retrieve a renderer to draw our characters. That said, it's just
    //       more readable for you to see the dynamic cast here.
    // NOTE: If dynamic_cast fails, you can check at run-time and handle through
    // either an
    //       assertion or exception the behavior.
    SDL_Renderer* renderer =
        dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();

    mRenderCtx.renderer = renderer;
    mRenderCtx.worldToCamera = mUpdateCtx.cameraCenter - mScreenCenter;

    // Render each of the character(s)
    for (GameObject* pGO : mGameObjects)
    {
        if (!pGO->IsActive()) continue;
        pGO->Render(&mRenderCtx);
    }

#ifdef GIZMOS
    mGizmosUtil.SetFillColor({0, 0, 0, 0xFF});
    mGizmosUtil.SetStrokeColor({0, 0, 0, 0xFF});
    mGizmosUtil.SetRenderContext(&mRenderCtx);
    mGizmosUtil.SetDrawMode(util::Gizmos::DrawMode::DM_NONE);

    for (GameObject* pGO : mGameObjects)
    {
        if (!pGO->IsActive()) continue;
        pGO->DrawGizmos(&mRenderCtx, &mGizmosUtil);
    }
#endif

    // Flip the buffer to render
    mRenderer->RenderPresent();
}

// check if colliding
bool Engine::IsColliding(ColliderComponent* collider, FRect* rectangle)
{
    // loop through gameobjects
    for (GameObject* object : mGameObjects)
    {
        if (!object->IsActive()) continue;

        if (object->IsColliding(collider, rectangle))
        {
            return true;
        }
    }
    return false;
}

// Loops forever!
void Engine::RunGameLoop()
{
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    int frameIdx = 0;
    // While application is running
    while (!quit)
    {
        // Get user input
        Input(&quit);
        // If you have time, implement your frame capping code here
        // Otherwise, this is a cheap hack for this lab.
        SDL_Delay(16);
        // Update our scene with the context
        mUpdateCtx.deltaTime = 0.016f;
        Update();
        // Render using OpenGL
        mRenderCtx.frameIdx = frameIdx;
        Render();
        frameIdx++;
    }
    // Disable text input
    SDL_StopTextInput();
}

void Engine::Startup()
{
    // Report which subsystems are being initialized
    if (mRenderer != nullptr)
    {
        std::cout << "Initializing Graphics Subsystem\n";
    }
    else
    {
        std::cout << "No Graphics Subsystem initialized\n";
    }

    SDLGraphicsEngineRenderer* graphicsEngine =
        dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer);
    SDL_Renderer* renderer = graphicsEngine->GetRenderer();
    ResourceManager::instance().Startup(renderer);

    if (mInput)
    {
        Uint32 windowId = SDL_GetWindowID(graphicsEngine->GetWindow());
        mInput->SetMainWindow(windowId);
    }
}

void Engine::Shutdown()
{
    // Destroy all game objects
    mGameObjects.clear();

    ResourceManager::instance().Shutdown();

    // Shut down our Graphics Subsystem
    if (nullptr != mRenderer)
    {
        delete mRenderer;
    }

    // Shut down our Input System
    if (nullptr != mInput)
    {
        delete mInput;
    }
}

void Engine::InitializeGraphicsSubSystem()
{
    // Setup our Renderer
    mScreenSize = glm::vec2(1280, 720);
    mScreenCenter = mScreenSize * 0.5f;
    mRenderer = new SDLGraphicsEngineRenderer(mScreenSize.x, mScreenSize.y);
    if (nullptr == mRenderer)
    {
        exit(1);  // Terminate program if renderer
                  // cannot be created.
                  // (Optional) TODO:   Could put an error
                  //                    messeage, or try to
                  //                    reinitialize the engine
                  //                    with a different render
    }
}

InputState* Engine::InitializeInputSystem()
{
    // Setup our input manager
    mInput = new InputManager();
    return mInput;
}

GameObject& Engine::InstantiateGameObject()
{
    mGameObjects.push_back(new GameObject(this));
    return *mGameObjects.back();
}
