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

    /**
     * Sets the tile size
     * @param srcTileWidth Width
     * @param srcTileHeight Height
     */
    void SetTileSize(unsigned int srcTileWidth, unsigned srcTileHeight);

    /**
     * Sets the sprite size
     * @param srcTileWidth Width
     * @param srcTileHeight Height
     */
    void SetSpriteSize(unsigned int srcTileWidth, unsigned srcTileHeight);

    /**
     * Get the maximum number of tiles in the spritesheet.
     * Note: Does not ignore blank tiles.
     * @return Max number of tiles
     */
    unsigned int Count();

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

    /**
     * Gets the number of columns in the spritesheet
     * @return The number of columns
     */
    unsigned int GetSpritesheetCols();

    /**
     * Gets the number of rows in the spritesheet
     * @return The number of rows
     */
    unsigned int GetSpritesheetRows();

private:
    std::shared_ptr<SDL_Texture> mTexture;
    int mTextureWidth;
    int mTextureHeight;
    int mRows;
    int mCols;
    int mSrcTileWidth;
    int mSrcTileHeight;
};

#endif
