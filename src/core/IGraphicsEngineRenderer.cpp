#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "core/IGraphicsEngineRenderer.hpp"
///////////////////////////////////////////////////////////////////
/// (Other Render implementations here (e.g. Direct3D)
///////////////////////////////////////////////////////////////////

// ...

///////////////////////////////////////////////////////////////////
/// SDLGraphicsEngineRenderer Implementation
//////////////////////////////////////////////////////////////////
SDLGraphicsEngineRenderer::SDLGraphicsEngineRenderer(int w, int h)
    : IGraphicsEngineRenderer(w, h)
{
    // Initialize random number generation.
    srand(time(nullptr));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
                  << "\n";
        exit(1);
    }

    // Create window
    mWindow = SDL_CreateWindow("Ms. Pajama's Game", 100, 100, mScreenWidth,
                               mScreenHeight, SDL_WINDOW_SHOWN);
    std::cout << SDL_GetWindowID(mWindow) << std::endl;

    // Check if Window did not create.
    if (nullptr == mWindow)
    {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
        exit(1);
    }

    // Create a Renderer to draw on
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    // Check if Renderer did not create.
    if (nullptr == mRenderer)
    {
        std::cerr << "Renderer could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
        exit(1);
    }

    // SDL Setup successfully
    std::cout << "No SDL errors Detected in during init\n\n";
}

SDLGraphicsEngineRenderer::~SDLGraphicsEngineRenderer()
{
    // Destroy Renderer
    SDL_DestroyRenderer(mRenderer);
    // Destroy window
    SDL_DestroyWindow(mWindow);
    mRenderer = nullptr;
    mWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void SDLGraphicsEngineRenderer::SetRenderDrawColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
}

void SDLGraphicsEngineRenderer::RenderClear() { SDL_RenderClear(mRenderer); }

void SDLGraphicsEngineRenderer::RenderPresent()
{
    SDL_RenderPresent(mRenderer);
}

// Get Pointer to Window
SDL_Window* SDLGraphicsEngineRenderer::GetWindow() { return mWindow; }

// Get Pointer to Renderer
SDL_Renderer* SDLGraphicsEngineRenderer::GetRenderer() { return mRenderer; }
