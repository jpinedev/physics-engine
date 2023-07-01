#include "core/SpriteRenderer.hpp"
#include <stdexcept>
#include "core/RenderContext.hpp"
#include "core/ResourceManager.hpp"
#include "core/UpdateContext.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

SpriteRenderer::SpriteRenderer() : Component("sprite") {}

SpriteRenderer::~SpriteRenderer()
{
    if (mSpritesheet)
        ResourceManager::instance().Spritesheets()->Destroy(mSpritesheet);
}

void SpriteRenderer::Render(RenderContext* ren)
{
    if (!mSpritesheet)
    {
        throw std::runtime_error(
            "SpriteRenderer does not have an assigned Spritesheet.");
    }
    const glm::vec2& pos = mGameObject->GetTransform().GetPosition();
    mDest.x = pos.x - ren->worldToCamera.x;
    mDest.y = pos.y - ren->worldToCamera.y;
    mSpritesheet->DrawSpriteAt(ren, mSpriteIndex, mDest);
}

void SpriteRenderer::UseSpritesheet(std::shared_ptr<Spritesheet> spritesheet)
{
    mSpritesheet = spritesheet;
    mSpriteIndex %= mSpritesheet->Count();
}
