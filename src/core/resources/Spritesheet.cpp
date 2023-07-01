#include "core/resources/Spritesheet.hpp"

#include <algorithm>

Spritesheet::Spritesheet(std::shared_ptr<SDL_Texture> texture)
    : mTexture(texture), mSize(1, 1)
{
    int width, height;
    SDL_QueryTexture(mTexture.get(), NULL, NULL, &width, &height);
    mTextureSize = mSpriteSize = Size2D{width, height};
}

Spritesheet::Spritesheet(Spritesheet&& other) noexcept
{
    mTexture = std::move(other.mTexture);
    other.mTexture = NULL;

    mTextureSize = other.mTextureSize;
    mSize = other.mSize;
    mSpriteSize = other.mSpriteSize;
}

Spritesheet::~Spritesheet()
{
    if (mTexture) mTexture.reset();
}

void Spritesheet::SetSpriteSize(Size2D size)
{
    mSpriteSize = size;

    mSize.x = mTextureSize.x / mSpriteSize.x;
    mSize.y = mTextureSize.y / mSpriteSize.y;
}

void Spritesheet::DrawTileAt(RenderContext* renderContext,
                             unsigned int tileIndex, SDL_Rect& dest,
                             bool hasCollider)
{
    SDL_Rect src;
    // Reverse lookup, given the tile type
    // and then figuring out how to select it
    // from the texture atlas.
    src.x = (tileIndex % mSize.x) * mSpriteSize.x;
    src.y = (tileIndex / mSize.x) * mSpriteSize.y;
    src.w = mSpriteSize.x;
    src.h = mSpriteSize.y;

    SDL_RenderCopy(renderContext->renderer, mTexture.get(), &src, &dest);
}
void Spritesheet::DrawSpriteAt(RenderContext* renderContext,
                               unsigned int spriteIndex, SDL_Rect& dest)
{
    DrawTileAt(renderContext, spriteIndex, dest);
}
