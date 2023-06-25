#ifndef __TILEMAPDATA_HPP__
#define __TILEMAPDATA_HPP__

#include <deque>
#include <forward_list>
#include <iostream>

#include "core/TinyMath.hpp"

/**
 * Represents the tile index and whether
 * if it is a collider.
 *
 * The tile index is the index into the texture atlas
 * so that it knows that texture it is.
 */
struct TileData
{
    int type = -1;
    bool collider = false;
};
std::istream& operator>>(std::istream& in, TileData& tile);
std::ostream& operator<<(std::ostream& out, const TileData& tile);
inline bool operator==(const TileData& lhs, const TileData& rhs);

/**
 * A dynamic data structure for storing a tile map.
 */
class TilemapData
{
public:
    ~TilemapData();

    /**
     * Gets the tile in the given x and y position in this tile map.
     *
     * @param x the x position
     * @param y the y position
     * @return the tile data
     */
    TileData GetTile(int x, int y) const noexcept;
    /**
     * Gets the tile in the given Vec2D position in this tile map.
     *
     * @param tilePos the position of the tile
     * @return the tile data
     */
    inline TileData GetTile(Vec2D tilePos) const noexcept;

    /**
     * Sets the given tile data in the given x and y position.
     *
     * @param x the x position
     * @param y the y position
     * @param tileData the tile data to set
     */
    void SetTile(int x, int y, TileData tileData) noexcept;
    /**
     * Sets the given tile data in the given Vec2D position.
     *
     * @param tilePos the position of the tile
     * @param tileData the tile data to set
     */
    inline void SetTile(Vec2D tilePos, TileData tileData) noexcept;

    /**
     * Gets the width of this tile map.
     *
     * @return the width as integer
     */
    unsigned int GetWidth() const;
    /**
     * Gets the hight of this tile map.
     *
     * @return the height as integer.
     */
    unsigned int GetHeight() const;

    void Print(std::ostream& out = std::cout) const;

private:
    std::deque<std::deque<TileData> > mTileData;
    unsigned int mWidth = 0, mHeight = 0;

    /**
     * Create an empty TilemapData.
     *
     * WARN: TilemapData must be at least 1x1 to be used.
     *       Call EnsureAtLeast1x1() to make valid,
     *       or use the EmplaceRows/EmplaceCols methods to grow the TilemapData.
     */
    TilemapData();
    /**
     * Create a TilemapData from a preconstructed 2D array.
     *
     * WARN: Assumes that the 2D list is not jagged and has dimensions h x w
     * (row major).
     */
    TilemapData(unsigned int w, unsigned int h,
                std::deque<std::deque<TileData> > tileData);

    /**
     * Pops the given number of rows from the front.
     *
     * @param count the number to pop
     */
    void PopRowsFront(unsigned int count);
    /**
     * Pops the given number of rows from the back.
     *
     * @param count the number to pop
     */
    void PopRowsBack(unsigned int count);
    /**
     * Pops the given number of cols from the front.
     *
     * @param count the number to pop
     */
    void PopColsFront(unsigned int count);
    /**
     * Pops the given number of cols from the back.
     *
     * @param count the number to pop
     */
    void PopColsBack(unsigned int count);

    /**
     * Emplaces the given number of rows from the front.
     *
     * @param count the number to emplace
     */
    void EmplaceRowsFront(unsigned int count);
    /**
     * Emplaces the given number of rows from the back.
     *
     * @param count the number to emplace
     */
    void EmplaceRowsBack(unsigned int count);
    /**
     * Emplaces the given number of cols from the front.
     *
     * @param count the number to emplace
     */
    void EmplaceColsFront(unsigned int count);
    /**
     * Emplaces the given number of cols from the back.
     *
     * @param count the number to emplace
     */
    void EmplaceColsBack(unsigned int count);

    /**
     * Remove any empty leading or trailing rows and columns.
     *
     * WARN: When there are no tiles in the map, the map will shrink to 1x1.
     */
    void ShrinkToFit();
    /**
     * Grows this tile map to fit the given width and height.
     *
     * @param x the width
     * @param y the height
     */
    void GrowToFit(int x, int y);

    /**
     * If the map is empty, make it 1x1 with only a default tile.
     */
    void EnsureAtLeast1x1();

    friend class TilemapLoader;
};

#endif
