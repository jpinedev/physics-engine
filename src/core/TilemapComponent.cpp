#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

#include "core/ResourceManager.hpp"
#include "core/TilemapComponent.hpp"
#include "core/collision/TilemapColliderComponent.hpp"
#include "core/resources/Spritesheet.hpp"
#include "core/resources/TilemapData.hpp"

// Creates a new tile map.
// rows and cols are how many different tiles there are in the sprite sheet
//
// _TileWidth and _TileHeight are the size of each individual
// tile in the sprite sheet.
// (Typically this works best if they are square for this implementation.)
//
// _mapX, and _mapY are the size of the tilemap. This is the actual
// number of tiles in the game that the player sees, not how many tiles
// are in the actual sprite sheet file loaded.
TilemapComponent::TilemapComponent(std::shared_ptr<Spritesheet>& textureAtlas)
    : Component("tile_map"), mTextureAtlas(textureAtlas)
{
}

// Destructor
TilemapComponent::~TilemapComponent()
{
    ResourceManager::instance().Tilemaps()->Destroy(mMapData);
}

void TilemapComponent::SetDisplayTileSize(unsigned int width,
                                          unsigned int height)
{
    mDestTileWidth = width;
    mDestTileHeight = height;
}

// render TilemapComponent
void TilemapComponent::Render(RenderContext* ren)
{
    if (nullptr == ren)
    {
        SDL_Log("No valid renderer found");
    }
    if (!mTextureAtlas)
    {
        // TODO: create a default spritesheet with a default tile to show for
        // debugging that will eliminate the need for this check here
        SDL_Log("No valid spritesheet has been set");
        return;
    }

    SDL_Rect Dest;
    int mapWidth = mMapData->GetWidth();
    int mapHeight = mMapData->GetHeight();
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            // Select our Tile
            int currentTile = mMapData->GetTile(x, y).type;
            bool hasCollider = mMapData->GetTile(x, y).collider;
            if (currentTile > -1)
            {
                GetTileDisplayRect(&Dest, ren, x, y);
                mTextureAtlas->DrawTileAt(ren, currentTile, Dest, hasCollider);
            }
        }
    }
}

void TilemapComponent::GenerateMapFromFile(std::string filePath)
{
    ResourceManager::instance().Tilemaps()->Load(filePath);
    mMapData = ResourceManager::instance().Tilemaps()->Get(filePath);

    mMapData->Print();
}

void TilemapComponent::GetTileDisplayRect(SDL_Rect* out_rect,
                                          RenderContext* ren, int x, int y)
{
    out_rect->x = x * mDestTileWidth - ren->worldToCamera.x;
    out_rect->y = y * mDestTileHeight - ren->worldToCamera.y;
    out_rect->w = mDestTileWidth;
    out_rect->h = mDestTileHeight;
}

Vec2D TilemapComponent::WorldPosToTilePos(Vec2D& worldPos)
{
    return Vec2D(floorf(worldPos.x / mDestTileWidth),
                 floorf(worldPos.y / mDestTileHeight));
}

std::shared_ptr<TilemapData> TilemapComponent::GetTileMapData()
{
    return mMapData;
}
