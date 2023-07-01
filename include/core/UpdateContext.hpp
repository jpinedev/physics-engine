#ifndef __UPDATECONTEXT_HPP__
#define __UPDATECONTEXT_HPP__

#include <glm/vec2.hpp>

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
    glm::vec2 cameraCenter;
    float deltaTime;
};

#endif
