#ifndef __UPDATECONTEXT_HPP__
#define __UPDATECONTEXT_HPP__

#include "core/TinyMath.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

/**
 * Represents the context for updating,
 * passed by the main game loop down
 * to the components so that they have the information
 * they need to update.
 */
struct UpdateContext
{
    Vec2D cameraCenter;
    float deltaTime;
};

#endif
