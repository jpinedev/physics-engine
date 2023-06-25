#include "core/resources/Spritesheet.hpp"

#include <algorithm>

Spritesheet::Spritesheet(std::shared_ptr<SDL_Texture> texture)
    : mTexture(texture), mRows(1), mCols(1)
{
    SDL_QueryTexture(mTexture.get(), NULL, NULL, &mTextureWidth,
                     &mTextureHeight);
    mSrcTileHeight = mTextureHeight;
    mSrcTileWidth = mTextureWidth;
}

Spritesheet::Spritesheet(Spritesheet&& other) noexcept
{
    mTexture = std::move(other.mTexture);
    other.mTexture = NULL;

    mTextureWidth = other.mTextureWidth;
    mTextureHeight = other.mTextureHeight;

    mRows = other.mRows;
    mCols = other.mCols;

    mSrcTileHeight = other.mSrcTileHeight;
    mSrcTileWidth = other.mSrcTileWidth;
}

Spritesheet::~Spritesheet()
{
    if (mTexture) mTexture.reset();
}

void Spritesheet::SetTileSize(unsigned int srcTileWidth,
                              unsigned int srcTileHeight)
{
    mSrcTileWidth = srcTileWidth;
    mSrcTileHeight = srcTileHeight;

    mCols = mTextureWidth / mSrcTileWidth;
    mRows = mTextureHeight / mSrcTileHeight;
}
void Spritesheet::SetSpriteSize(unsigned int srcSpriteWidth,
                                unsigned int srcSpriteHeight)
{
    SetTileSize(srcSpriteWidth, srcSpriteHeight);
}

unsigned int Spritesheet::Count() { return mRows * mCols; }

void Spritesheet::DrawTileAt(RenderContext* renderContext,
                             unsigned int tileIndex, SDL_Rect& dest,
                             bool hasCollider)
{
    SDL_Rect src;
    // Reverse lookup, given the tile type
    // and then figuring out how to select it
    // from the texture atlas.
    src.x = (tileIndex % mCols) * mSrcTileWidth;
    src.y = (tileIndex / mCols) * mSrcTileHeight;
    src.w = mSrcTileWidth;
    src.h = mSrcTileHeight;

    SDL_RenderCopy(renderContext->renderer, mTexture.get(), &src, &dest);
}
void Spritesheet::DrawSpriteAt(RenderContext* renderContext,
                               unsigned int spriteIndex, SDL_Rect& dest)
{
    DrawTileAt(renderContext, spriteIndex, dest);
}

unsigned int Spritesheet::GetSpritesheetCols() { return mCols; }
unsigned int Spritesheet::GetSpritesheetRows() { return mRows; }
