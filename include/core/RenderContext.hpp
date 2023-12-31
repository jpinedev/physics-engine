#ifndef __RENDERCONTEXT_HPP__
#define __RENDERCONTEXT_HPP__

#include <glm/vec2.hpp>
#include "core/IGraphicsEngineRenderer.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

struct RenderContext
{
    SDL_Renderer* renderer;
    glm::vec2 worldToCamera;
    int frameIdx;

    inline SDL_Rect& WorldToCamera(SDL_Rect& rect);
};

inline SDL_Rect& RenderContext::WorldToCamera(SDL_Rect& rect)
{
    rect.x -= worldToCamera.x;
    rect.y -= worldToCamera.y;
    return rect;
}

#endif
