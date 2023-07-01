#ifndef __SDLCONVERSIONS_HPP__
#define __SDLCONVERSIONS_HPP__

#include <glm/vec2.hpp>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

struct FRect
{
    union
    {
        struct
        {
            float x{0}, y{0}, w{0}, h{0};
        };
        struct
        {
            glm::vec2 pos, size;
        };
    };

    FRect(glm::vec2 pos, glm::vec2 size) : pos(pos), size(size) {}
    FRect(const SDL_Rect& rect) : x(rect.x), y(rect.y), w(rect.w), h(rect.h) {}
    FRect& operator=(const SDL_Rect& rect)
    {
        x = rect.x;
        y = rect.y;
        w = rect.w;
        h = rect.h;
        return *this;
    }
    operator SDL_Rect() const
    {
        return SDL_Rect{(int)x, (int)y, (int)w, (int)h};
    }
};

bool HasIntersection(FRect lhs, FRect rhs);

#endif
