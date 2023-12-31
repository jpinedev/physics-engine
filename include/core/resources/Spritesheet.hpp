#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>

#endif
#include <memory>
#include <string>

#include "core/RenderContext.hpp"

typedef glm::uvec2 Size2D;

/**
 * This represents the notion of a spritesheet/texture atlas,
 * i.e an image file that is actually composed of smaller textures, but
 * has been put into one file so that they can be loaded into engine
 * as one unit.
 *
 * It is currently assumed that the sprites all have the same
 * width height, and have no gaps with each other.
 */
class Spritesheet
{
public:
    Spritesheet(std::shared_ptr<SDL_Texture> texture);
    Spritesheet(Spritesheet&& other) noexcept;
    ~Spritesheet();

    void SetSpriteSize(Size2D spriteSize);
    inline void SetTileSize(Size2D tileSize) { SetSpriteSize(tileSize); }

    /**
     * Get the maximum number of tiles in the spritesheet.
     * Note: Does not ignore blank tiles.
     * @return Max number of tiles
     */
    inline unsigned int Count() { return mSize.x * mSize.y; }

    /**
     * Draws tile at the desired spot with the details given
     * @param renderContext The render data
     * @param tileIndex The index of the tile
     * @param dest The destination of the tile
     * @param hasCollider Does the tile have a collider?
     */
    void DrawTileAt(RenderContext* renderContext, unsigned int tileIndex,
                    SDL_Rect& dest, bool hasCollider = false);

    /**
     * Draws a sprite to the destination
     * @param renderCtx The render data
     * @param spriteIndex The index of the sprite
     * @param dest The destination of the sprite
     */
    void DrawSpriteAt(RenderContext* renderCtx, unsigned int spriteIndex,
                      SDL_Rect& dest);

    inline Size2D GetSize() { return mSize; }

private:
    std::shared_ptr<SDL_Texture> mTexture;
    Size2D mTextureSize{0, 0};
    Size2D mSize{0, 0};
    Size2D mSpriteSize{0, 0};
};

#endif
