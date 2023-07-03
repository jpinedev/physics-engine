#ifndef __BOUNDINGBOX_HPP__
#define __BOUNDINGBOX_HPP__

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <initializer_list>
#include "core/util/SDLConversions.hpp"

struct Bounds
{
    union
    {
        struct
        {
            float left{0}, top{0}, right{0}, bottom{0};
        };
        struct
        {
            glm::vec2 min, max;
        };
    };

    Bounds(std::initializer_list<glm::vec2> toContain) noexcept;
    Bounds(std::initializer_list<Bounds> toContain) noexcept;
    Bounds(const FRect& rect) : min(rect.pos), max(min + rect.size) {}
    FRect ToFRect() const { return FRect(min, max - min); }
    bool GetOverlap(const Bounds& other, Bounds* out_overlap = NULL) const;

private:
    bool mbInitialized{false};
};

#endif
