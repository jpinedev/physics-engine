#ifndef __TILEMAPDATA_HPP__
#define __TILEMAPDATA_HPP__

#include <deque>
#include <forward_list>
#include <iostream>

#include <glm/vec2.hpp>

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
    bool bHasCollider = false;
};
std::istream& operator>>(std::istream& in, TileData& tile);
std::ostream& operator<<(std::ostream& out, const TileData& tile);
inline bool operator==(const TileData& lhs, const TileData& rhs);

typedef glm::ivec2 TileLoc;
typedef glm::uvec2 Size2D;

/**
 * A dynamic data structure for storing a tile map.
 */
class TilemapData
{
private:
    typedef std::deque<TileData> TileRow;
    typedef std::deque<TileRow> TileGrid;

public:
    ~TilemapData();

    TileData GetTile(TileLoc loc) const noexcept;
    void SetTile(TileLoc loc, TileData tileData) noexcept;

    inline Size2D GetSize() const { return mSize; }

    void Print(std::ostream& out = std::cout) const;

private:
    TileGrid mData;
    Size2D mSize{0, 0};

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
    TilemapData(Size2D size, const TileGrid& tileData);

    void PopRowsFront(unsigned int count);
    void PopRowsBack(unsigned int count);
    void PopColsFront(unsigned int count);
    void PopColsBack(unsigned int count);

    void EmplaceRowsFront(unsigned int count);
    void EmplaceRowsBack(unsigned int count);
    void EmplaceColsFront(unsigned int count);
    void EmplaceColsBack(unsigned int count);

    void ShrinkToFit();
    void GrowToFit(TileLoc tileLoc);

    /**
     * If the map is empty, make it 1x1 with only a default tile.
     */
    void EnsureAtLeast1x1();

    friend class TilemapLoader;
};

#endif
