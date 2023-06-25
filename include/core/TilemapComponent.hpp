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

    /**
     * Set the render size of a tile.
     *
     * @param width the width to set
     * @param height the width to set
     */
    void SetDisplayTileSize(unsigned int width, unsigned int height);

    /**
     * Draw all of the tiles in the tilemap.
     *
     * @param ren the render context for rendering
     */
    virtual void Render(RenderContext* ren) override;

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
    Vec2D WorldPosToTilePos(Vec2D& worldPos);

    /**
     * Gets the tile map data of this tile map.
     *
     * @return a shared pointer of the tile map data
     */
    std::shared_ptr<TilemapData> GetTileMapData();

private:
    // How big each tile is in the world.
    int mDestTileWidth;
    int mDestTileHeight;
    // Where our Tilemap is rendered
    // An SDL Surface contains pixel data to draw our Tilemap
    std::shared_ptr<Spritesheet>& mTextureAtlas;
    std::string mTextureFilePath;
    // Stores our tile types
    std::shared_ptr<TilemapData> mMapData;
};

#endif
