#include <limits>
#ifdef GIZMOS

#ifndef __GIZMOS_HPP__
#define __GIZMOS_HPP__

#include <glm/vec2.hpp>
#include "core/RenderContext.hpp"
#include "core/util/Bounds.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

#define FLOAT_MAX std::numeric_limits<float>::max()

namespace util
{

class Gizmos
{
public:
    enum DrawMode : uint8_t
    {
        DM_NONE = 0x0,
        DM_FILL = 0x1,
        DM_STROKE = 0x2,
        DM_FILL_STROKE = DM_FILL | DM_STROKE,
    };

public:
    void DrawLine(glm::vec2 start, glm::vec2 end);
    void DrawRect(SDL_Rect rect);
    void DrawRay(glm::vec2 start, glm::vec2 direction,
                 float length = FLOAT_MAX);
    void DrawRay(glm::vec2 start, float angleDeg, float length = FLOAT_MAX);
    void DrawCircle(glm::vec2 center, float radius);
    void DrawCapsule(glm::vec2 center, float height, float radius);

    void SetFillColor(SDL_Color fillColor) { mFillColor = fillColor; }
    void SetStrokeColor(SDL_Color strokeColor) { mStrokeColor = strokeColor; }
    void SetRenderContext(RenderContext* renderCtx) { mCtx = renderCtx; }
    void SetDrawMode(DrawMode drawMode) { mDrawMode = drawMode; }

private:
    SDL_Color mFillColor{0, 0, 0, 0};
    SDL_Color mStrokeColor{0, 0, 0, 0};
    RenderContext* mCtx = NULL;
    DrawMode mDrawMode = DrawMode::DM_NONE;
};

}  // namespace util

#endif  // __GIZMOS_HPP__

#endif  // GIZMOS
