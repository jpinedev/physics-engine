#include "SDL2/SDL_render.h"
#ifdef GIZMOS

#include "core/RenderContext.hpp"
#include "core/util/Gizmos.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

#define EscapeIfNecessary()                              \
    if (!mCtx || mDrawMode == DrawMode::DM_NONE) return; \
    SDL_Renderer* ren = mCtx->renderer;

#define ExpandColor(color) color.r, color.g, color.b, color.a

namespace util
{
void Gizmos::DrawLine(Vec2D start, Vec2D end) { throw; }
void Gizmos::DrawRect(SDL_Rect rect)
{
    EscapeIfNecessary();

    if (mDrawMode & DrawMode::DM_FILL)
    {
        SDL_SetRenderDrawColor(ren, ExpandColor(mFillColor));
        SDL_RenderFillRect(ren, &rect);
    }
    if (mDrawMode & DrawMode::DM_STROKE)
    {
        SDL_SetRenderDrawColor(ren, ExpandColor(mStrokeColor));
        SDL_RenderDrawRect(ren, &rect);
    }
}
void Gizmos::DrawRay(Vec2D start, Vec2D direction, float length) { throw; }
void Gizmos::DrawRay(Vec2D start, float angleDeg, float length) { throw; }
void Gizmos::DrawCircle(Vec2D center, float radius) { throw; }
void Gizmos::DrawCapsule(Vec2D center, float height, float radius) { throw; }
}  // namespace util

#endif  // GIZMOS
