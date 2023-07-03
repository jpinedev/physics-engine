#ifndef TILE_H
#define TILE_H

#include <memory>
#include <string>
#include <vector>

#include "core/Component.hpp"
#include "core/IGraphicsEngineRenderer.hpp"
#include "core/RenderContext.hpp"
#include "core/resources/Spritesheet.hpp"
#include "core/resources/TilemapData.hpp"

/**
 * This is a minimal implementation of a Tilemap
 */
class TilemapComponent : public Component
{
public:
    /**
     * Constructor for a tilemap
     */
    TilemapComponent(std::shared_ptr<Spritesheet>& textureAtlas);
    /**
     * Destructor for a tilemap
     */
    virtual ~TilemapComponent();

    virtual void Render(RenderContext* ren) override;

    void SetDisplayTileSize(Size2D size) { mTileDisplaySize = size; }

    /**
     * Given a file, generates a tile map.
     *
     * @param filePath the file path
     */
    void GenerateMapFromFile(std::string filePath);

    /**
     * Converts the given world position to tile position in this tile map.
     *
     * @param worldPos the world position to convert
     * @return the tile position in Vec2D
     */
    glm::vec2 WorldPosToTilePos(const glm::vec2& worldPos) const;
    glm::vec2 TileLocToLocalPos(const TileLoc& tileLoc) const;

    void GetTileDisplayRect(SDL_Rect* out_rect, RenderContext* ren,
                            TileLoc tile) const;

    /**
     * Gets the tile map data of this tile map.
     *
     * @return a shared pointer of the tile map data
     */
    std::shared_ptr<TilemapData> GetTileMapData();

private:
    // How big each tile is in the world.
    Size2D mTileDisplaySize{0, 0};
    // Where our Tilemap is rendered
    // An SDL Surface contains pixel data to draw our Tilemap
    std::shared_ptr<Spritesheet>& mTextureAtlas;
    std::string mTextureFilePath;
    // Stores our tile types
    std::shared_ptr<TilemapData> mMapData;
};

#endif
