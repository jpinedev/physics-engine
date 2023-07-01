#include "core/resources/TilemapData.hpp"
#include <glm/vec2.hpp>

#include <cassert>
#include <iomanip>

#define assertm(exp, msg) assert(((void)msg, exp))

std::istream& operator>>(std::istream& in, TileData& tile)
{
    in >> tile.type;
    char ch;
    in >> ch;
    tile.bHasCollider = (ch != '.');
    return in;
}

std::ostream& operator<<(std::ostream& out, const TileData& tile)
{
    out << tile.type << (tile.bHasCollider ? 'c' : '.');
    return out;
}

inline bool operator==(const TileData& lhs, const TileData& rhs)
{
    return lhs.type == rhs.type && lhs.bHasCollider == rhs.bHasCollider;
}

TilemapData::TilemapData() {}
TilemapData::TilemapData(Size2D size, const TileGrid& tileData)
    : mData(tileData), mSize(size)
{
    EnsureAtLeast1x1();
}
TilemapData::~TilemapData() {}

TileData TilemapData::GetTile(TileLoc tileLoc) const noexcept
{
    return (tileLoc.x < 0 || tileLoc.y < 0 || tileLoc.x >= mSize.x ||
            tileLoc.y >= mSize.y)
               ? TileData()
               : mData[tileLoc.y][tileLoc.x];
}

void TilemapData::SetTile(TileLoc tileLoc, TileData tileData) noexcept
{
    GrowToFit(tileLoc);

    if (tileLoc.x < 0) tileLoc.x = 0;
    if (tileLoc.y < 0) tileLoc.y = 0;

    if (tileData.type < -1) tileData.type = -1;

    mData[tileLoc.y][tileLoc.x] = tileData;
}

void TilemapData::Print(std::ostream& out) const
{
    for (const TileRow& row : mData)
    {
        for (const TileData& tile : row)
        {
            out << std::setw(4) << tile << ' ';
        }
        out << std::endl;
    }
}

void TilemapData::PopRowsFront(unsigned int count)
{
    for (int row = 0; row < count; ++row)
    {
        mData.pop_front();
    }
    mSize.y -= count;
}
void TilemapData::PopRowsBack(unsigned int count)
{
    for (int row = 0; row < count; ++row)
    {
        mData.pop_back();
    }
    mSize.y -= count;
}
void TilemapData::PopColsFront(unsigned int count)
{
    for (TileRow& row : mData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.pop_front();
        }
    }
    mSize.x -= count;
}
void TilemapData::PopColsBack(unsigned int count)
{
    for (TileRow& row : mData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.pop_back();
        }
    }
    mSize.x -= count;
}

void TilemapData::EmplaceRowsFront(unsigned int count)
{
    for (int row = 0; row < count; ++row)
    {
        mData.emplace_front(mSize.x);
    }
    mSize.y += count;
}
void TilemapData::EmplaceRowsBack(unsigned int count)
{
    for (int row = 0; row < count; ++row)
    {
        mData.emplace_back(mSize.x);
    }
    mSize.y += count;
}
void TilemapData::EmplaceColsFront(unsigned int count)
{
    for (TileRow& row : mData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.emplace_front();
        }
    }
    mSize.x += count;
}
void TilemapData::EmplaceColsBack(unsigned int count)
{
    for (TileRow& row : mData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.emplace_back();
        }
    }
    mSize.x += count;
}

void TilemapData::ShrinkToFit()
{
    int minX = mSize.x - 1, minY = mSize.y - 1;
    int maxX = 0, maxY = 0;

    TileData defaultTile;

    // Find the range of tiles that have data
    TileLoc tileLoc;
    for (tileLoc.y = 0; tileLoc.y < mSize.y; ++tileLoc.y)
    {
        for (tileLoc.x = 0; tileLoc.x < mSize.x; ++tileLoc.x)
        {
            if (GetTile(tileLoc) == defaultTile) continue;

            if (tileLoc.x < minX) minX = tileLoc.x;
            if (tileLoc.x > maxX) maxX = tileLoc.x;

            if (tileLoc.y < minY) minY = tileLoc.y;
            if (tileLoc.y > maxY) maxY = tileLoc.y;
        }
    }

    // Cut out all rows with no data
    int originalHeight = mSize.y;
    PopRowsFront(minY);
    PopRowsBack(originalHeight - maxY - 1);

    // Cut out all columns with no data
    int originalWidth = mSize.x;
    PopColsFront(minX);
    PopColsBack(originalWidth - maxX - 1);

    assertm(mSize.x == maxX - minX + 1,
            "Width of tile map data after shrink is not as expected.");
    assertm(mSize.y == maxY - minY + 1,
            "Width of tile map data after shrink is not as expected.");

    EnsureAtLeast1x1();
}

void TilemapData::GrowToFit(TileLoc tileLoc)
{
    if (tileLoc.x < 0)
        EmplaceColsFront(-tileLoc.x);
    else if (tileLoc.x >= mSize.x)
        EmplaceColsBack(tileLoc.x - mSize.x + 1);

    if (tileLoc.y < 0)
        EmplaceRowsFront(-tileLoc.y);
    else if (tileLoc.y >= mSize.y)
        EmplaceRowsBack(tileLoc.y - mSize.y + 1);
}

void TilemapData::EnsureAtLeast1x1()
{
    if (mSize.x > 0 && mSize.y > 0) return;

    mSize.x = 1;
    mSize.y = 1;
    mData.emplace_back();
    mData.back().emplace_back();
}
