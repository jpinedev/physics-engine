#include "core/collision/TilemapColliderComponent.hpp"
#include "core/TilemapComponent.hpp"
#include "core/TinyMath.hpp"
#include "core/TransformComponent.hpp"
#include "core/resources/TilemapData.hpp"

#include <stdexcept>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

TilemapColliderComponent::TilemapColliderComponent() : ColliderComponent() {}
TilemapColliderComponent::~TilemapColliderComponent() {}

bool TilemapColliderComponent::CollidesWithRectangle(SDL_Rect* rect)
{
    FindTilemapIfNull();

    Vec2D position = mGameObject->GetTransform().GetPosition();

    // Get the top left bounds of the tile that the rectangle *COULD* collide
    // with
    Vec2D topLeftCornerRect = Vec2D(rect->x, rect->y);
    Vec2D topLeftTilePos = mTilemap->WorldPosToTilePos(topLeftCornerRect);

    // Get the bottom right bounds of the tile that the rectangle *COULD*
    // collide with
    Vec2D bottomRightCornerRect = topLeftCornerRect + Vec2D(rect->w, rect->h);
    Vec2D bottomRightTilePos =
        mTilemap->WorldPosToTilePos(bottomRightCornerRect);

    // Loop through all of the tiles that the rect *MAY* collide with (if it has
    // a collider)
    for (int tilePosY = topLeftTilePos.y; tilePosY <= bottomRightTilePos.y;
         ++tilePosY)
    {
        for (int tilePosX = topLeftTilePos.x; tilePosX <= bottomRightTilePos.x;
             ++tilePosX)
        {
            TileData tile = mData->GetTile(tilePosX, tilePosY);
            if (tile.collider) return true;
        }
    }

    return false;
}

bool TilemapColliderComponent::RaycastColliderRectangle()
{
    throw std::logic_error(
        "Unimplemented function: Raycast using any collider that is NOT a "
        "TilemapCollider");
}

void TilemapColliderComponent::FindTilemapIfNull()
{
    if (mTilemap) return;

    mTilemap = (TilemapComponent*)mGameObject->GetComponent("tile_map");

    if (!mTilemap)
    {
        throw std::runtime_error(
            "TilemapCollider could not find a Tilemap on its game "
            "object.");
    }

    mData = mTilemap->GetTileMapData();
}

#ifdef GIZMOS
void TilemapColliderComponent::DrawGizmos(RenderContext* renderer,
                                          util::Gizmos* util)
{
    FindTilemapIfNull();

    util->SetDrawMode(util::Gizmos::DrawMode::DM_STROKE);
    util->SetStrokeColor({0, 0xFF, 0, 0xFF});

    SDL_Rect tileRect;
    for (unsigned int tileRowIdx = 0, tileRowEnd = mData->GetHeight();
         tileRowIdx < tileRowEnd; ++tileRowIdx)
    {
        for (unsigned int tileColIdx = 0, tileColEnd = mData->GetWidth();
             tileColIdx < tileColEnd; ++tileColIdx)
        {
            if (!mData->GetTile(tileColIdx, tileRowIdx).collider) continue;

            mTilemap->GetTileDisplayRect(&tileRect, renderer, tileColIdx,
                                         tileRowIdx);

            util->DrawRect(tileRect);
        }
    }

    // TODO: util->DrawRect(GetCollisionRect());
}
#endif
