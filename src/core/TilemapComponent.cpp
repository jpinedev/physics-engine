#include <fstream>
#include <glm/vec2.hpp>
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
    Size2D mapSize = mMapData->GetSize();

    TileLoc tileLoc;
    for (tileLoc.y = 0; tileLoc.y < mapSize.y; tileLoc.y++)
    {
        for (tileLoc.x = 0; tileLoc.x < mapSize.x; tileLoc.x++)
        {
            // Select our Tile
            const TileData& tile = mMapData->GetTile(tileLoc);
            if (tile.type < 0) continue;

            GetTileDisplayRect(&Dest, ren, tileLoc);
            mTextureAtlas->DrawTileAt(ren, tile.type, Dest, tile.bHasCollider);
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
                                          RenderContext* ren,
                                          TileLoc tile) const
{
    out_rect->x = tile.x * mTileDisplaySize.x - ren->worldToCamera.x;
    out_rect->y = tile.y * mTileDisplaySize.y - ren->worldToCamera.y;
    out_rect->w = mTileDisplaySize.x;
    out_rect->h = mTileDisplaySize.y;
}

glm::vec2 TilemapComponent::WorldPosToTilePos(const glm::vec2& worldPos) const
{
    return glm::vec2(worldPos.x / mTileDisplaySize.x,
                     worldPos.y / mTileDisplaySize.y);
}

glm::vec2 TilemapComponent::TileLocToLocalPos(const TileLoc& tileLoc) const
{
    return glm::vec2(tileLoc.x * mTileDisplaySize.x,
                     tileLoc.y * mTileDisplaySize.y);
}

std::shared_ptr<TilemapData> TilemapComponent::GetTileMapData()
{
    return mMapData;
}
