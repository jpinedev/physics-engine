#ifdef GIZMOS

#ifndef __GIZMOS_HPP__
#define __GIZMOS_HPP__

#include "core/RenderContext.hpp"
#include "core/TinyMath.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

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
    void DrawLine(Vec2D start, Vec2D end);
    void DrawRect(SDL_Rect rect);
    void DrawRay(Vec2D start, Vec2D direction, float length = FLOAT_MAX);
    void DrawRay(Vec2D start, float angleDeg, float length = FLOAT_MAX);
    void DrawCircle(Vec2D center, float radius);
    void DrawCapsule(Vec2D center, float height, float radius);

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
