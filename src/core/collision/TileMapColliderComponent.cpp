#include "core/collision/TilemapColliderComponent.hpp"
#include "core/TilemapComponent.hpp"
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

bool TilemapColliderComponent::CollidesWithRectangle(FRect* rect)
{
    FindTilemapIfNull();

    glm::vec2 position = mGameObject->GetTransform().GetPosition();

    // Get the top left bounds of the tile that the rectangle *COULD* collide
    // with
    glm::vec2 topLeftCornerRect = glm::vec2(rect->x, rect->y);
    glm::vec2 topLeftTilePos = mTilemap->WorldPosToTilePos(topLeftCornerRect);

    // Get the bottom right bounds of the tile that the rectangle *COULD*
    // collide with
    glm::vec2 bottomRightCornerRect =
        topLeftCornerRect + glm::vec2(rect->w, rect->h);
    glm::vec2 bottomRightTilePos =
        mTilemap->WorldPosToTilePos(bottomRightCornerRect);

    // Loop through all of the tiles that the rect *MAY* collide with (if it has
    // a collider)
    TileLoc tileLoc;
    for (tileLoc.y = topLeftTilePos.y; tileLoc.y <= bottomRightTilePos.y;
         ++tileLoc.y)
    {
        for (tileLoc.x = topLeftTilePos.x; tileLoc.x <= bottomRightTilePos.x;
             ++tileLoc.x)
        {
            TileData tile = mData->GetTile(tileLoc);
            if (tile.bHasCollider) return true;
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

void TilemapColliderComponent::GetBoundingBoxes(std::vector<Bounds>& out_bounds)
{
    Size2D tilemapSize = mData->GetSize();
    out_bounds.reserve(tilemapSize.x * tilemapSize.y);

    glm::vec2 pos = mGameObject->GetTransform().GetPosition();

    TileLoc tileLoc;
    for (tileLoc.y = 0; tileLoc.y < tilemapSize.y; ++tileLoc.y)
    {
        for (tileLoc.x = 0; tileLoc.x < tilemapSize.x; ++tileLoc.x)
        {
            if (!mData->GetTile(tileLoc).bHasCollider) continue;

            out_bounds.emplace_back(
                mTilemap->TileLocToLocalPos(tileLoc) + pos,
                mTilemap->TileLocToLocalPos(tileLoc + glm::ivec2{1, 1}) + pos);
        }
    }
    out_bounds.shrink_to_fit();
}

#ifdef GIZMOS
void TilemapColliderComponent::DrawGizmos(RenderContext* renderer,
                                          util::Gizmos* util)
{
    FindTilemapIfNull();

    util->SetDrawMode(util::Gizmos::DrawMode::DM_STROKE);
    util->SetStrokeColor({0, 0xFF, 0, 0xFF});

    SDL_Rect tileRect;

    Size2D tilemapSize = mData->GetSize();
    TileLoc tileLoc;
    for (tileLoc.y = 0; tileLoc.y < tilemapSize.y; ++tileLoc.y)
    {
        for (tileLoc.x = 0; tileLoc.x < tilemapSize.x; ++tileLoc.x)
        {
            if (!mData->GetTile(tileLoc).bHasCollider) continue;

            mTilemap->GetTileDisplayRect(&tileRect, renderer, tileLoc);

            util->DrawRect(tileRect);
        }
    }

    // TODO: util->DrawRect(GetCollisionRect());
}
#endif
