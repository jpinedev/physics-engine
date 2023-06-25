#include "core/resources/TilemapData.hpp"
#include "core/TinyMath.hpp"

#include <iomanip>

std::istream& operator>>(std::istream& in, TileData& tile)
{
    in >> tile.type;
    char ch;
    in >> ch;
    tile.collider = (ch != '.');
    return in;
}

std::ostream& operator<<(std::ostream& out, const TileData& tile)
{
    out << tile.type << (tile.collider ? 'c' : '.');
    return out;
}

inline bool operator==(const TileData& lhs, const TileData& rhs)
{
    return lhs.type == rhs.type && lhs.collider == rhs.collider;
}

TilemapData::TilemapData() {}
TilemapData::TilemapData(unsigned int w, unsigned int h,
                         std::deque<std::deque<TileData> > tileData)
    : mTileData(tileData), mWidth(w), mHeight(h)
{
    EnsureAtLeast1x1();
}
TilemapData::~TilemapData() {}

TileData TilemapData::GetTile(int x, int y) const noexcept
{
    if (x < 0 || y < 0 || x >= mWidth || y >= mHeight) return TileData();

    return mTileData[y][x];
}
inline TileData TilemapData::GetTile(Vec2D tilePos) const noexcept
{
    return GetTile((int)tilePos.x, (int)tilePos.y);
}

void TilemapData::SetTile(int x, int y, TileData tileData) noexcept
{
    GrowToFit(x, y);
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    if (tileData.type < -1) tileData.type = -1;
    mTileData[y][x] = tileData;
}
inline void TilemapData::SetTile(Vec2D tilePos, TileData tileData) noexcept
{
    SetTile((int)tilePos.x, (int)tilePos.y, tileData);
}

unsigned int TilemapData::GetWidth() const { return mWidth; }
unsigned int TilemapData::GetHeight() const { return mHeight; }

void TilemapData::Print(std::ostream& out) const
{
    for (auto& row : mTileData)
    {
        for (auto& tile : row)
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
        mTileData.pop_front();
    }
    mHeight -= count;
}
void TilemapData::PopRowsBack(unsigned int count)
{
    for (int row = 0; row < count; ++row)
    {
        mTileData.pop_back();
    }
    mHeight -= count;
}
void TilemapData::PopColsFront(unsigned int count)
{
    for (auto& row : mTileData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.pop_front();
        }
    }
    mWidth -= count;
}
void TilemapData::PopColsBack(unsigned int count)
{
    for (auto& row : mTileData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.pop_back();
        }
    }
    mWidth -= count;
}

void TilemapData::EmplaceRowsFront(unsigned int count)
{
    for (int row = 0; row < count; ++row)
    {
        mTileData.emplace_front(mWidth);
    }
    mHeight += count;
}
void TilemapData::EmplaceRowsBack(unsigned int count)
{
    for (int row = 0; row < count; ++row)
    {
        mTileData.emplace_back(mWidth);
    }
    mHeight += count;
}
void TilemapData::EmplaceColsFront(unsigned int count)
{
    for (auto& row : mTileData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.emplace_front();
        }
    }
    mWidth += count;
}
void TilemapData::EmplaceColsBack(unsigned int count)
{
    for (auto& row : mTileData)
    {
        for (int col = 0; col < count; ++col)
        {
            row.emplace_back();
        }
    }
    mWidth += count;
}

void TilemapData::ShrinkToFit()
{
    int minX = mWidth - 1, minY = mHeight - 1;
    int maxX = 0, maxY = 0;

    TileData defaultTile;

    // Find the range of tiles that have data
    for (int row = 0; row < mHeight; ++row)
    {
        for (int col = 0; col < mWidth; ++col)
        {
            if (GetTile(col, row) == defaultTile) continue;

            if (col < minX) minX = col;
            if (col > maxX) maxX = col;

            if (row < minY) minY = row;
            if (row > maxY) maxY = row;
        }
    }

    // Cut out all rows with no data
    int originalHeight = mHeight;
    PopRowsFront(minY);
    PopRowsBack(originalHeight - maxY - 1);

    // Cut out all columns with no data
    int originalWidth = mWidth;
    PopColsFront(minX);
    PopColsBack(originalWidth - maxX - 1);

    assertm(mWidth == maxX - minX + 1,
            "Width of tile map data after shrink is not as expected.");
    assertm(mHeight == maxY - minY + 1,
            "Width of tile map data after shrink is not as expected.");

    EnsureAtLeast1x1();
}

void TilemapData::GrowToFit(int x, int y)
{
    if (x < 0)
    {
        EmplaceColsFront(-x);
    }
    else if (x >= mWidth)
    {
        EmplaceColsBack(x - mWidth + 1);
    }

    if (y < 0)
    {
        EmplaceRowsFront(-y);
    }
    else if (y >= mHeight)
    {
        EmplaceRowsBack(y - mHeight + 1);
    }
}

void TilemapData::EnsureAtLeast1x1()
{
    if (mWidth == 0 || mHeight == 0)
    {
        mWidth = 1;
        mHeight = 1;
        mTileData = std::deque<std::deque<TileData> >();
        mTileData.emplace_back();
        mTileData.back().emplace_back();
    }
}
