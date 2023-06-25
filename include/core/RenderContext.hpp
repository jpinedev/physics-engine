#ifndef __RENDERCONTEXT_HPP__
#define __RENDERCONTEXT_HPP__

#include "core/IGraphicsEngineRenderer.hpp"
#include "core/TinyMath.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

struct RenderContext
{
    SDL_Renderer* renderer;
    Vec2D worldToCamera;
    int frameIdx;
};

#endif
