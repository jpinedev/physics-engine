#include "core/resources/TilemapLoader.hpp"
#include "core/resources/TilemapData.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <tuple>

TilemapLoader::TilemapLoader() {}
TilemapLoader::~TilemapLoader() {}

void TilemapLoader::Load(std::string fileLoc)
{
    std::ifstream file;
    file.open(fileLoc);

    std::string line;
    TileData tile;

    unsigned int maxCols = 0;
    mResources.emplace(fileLoc, new TilemapData());
    TilemapData& mapData = *mResources[fileLoc];

    if (!file.is_open())
    {
        throw std::invalid_argument("Tilemap file could not be found.");
    }

    int y = 0;
    while (file.good() && !file.eof())
    {
        std::getline(file, line);
        if (line.empty() || file.eof()) break;

        int x = 0;
        std::stringstream ss(line);

        while (ss >> tile)
        {
            mapData.SetTile(x, y, tile);
            x++;
        }
        if (x < maxCols || (maxCols != 0 && x > maxCols))
        {
            throw std::invalid_argument(
                "Tilemap is jagged. Tilemaps must be rectangular.");
        }

        if (x > maxCols) maxCols = x;
        ++y;
    }

    file.close();
}

void TilemapLoader::Save(std::shared_ptr<TilemapData>& resource)
{
    if (!resource)
    {
        throw std::invalid_argument("Trying to save an invalid resource");
    }

    auto resourceIt = FindByPtr(resource);
    if (resourceIt == mResources.end())
    {
        throw std::invalid_argument("Trying to save an invalid resource");
    }

    std::string fileLoc = resourceIt->first;
    TilemapData& mapData = *resourceIt->second;

    mapData.ShrinkToFit();

    std::ofstream outFile(fileLoc);

    if (!outFile.is_open())
    {
        throw std::runtime_error("Could not save to file '" + fileLoc + "'");
    }

    int mapWidth = mapData.GetWidth();
    int mapHeight = mapData.GetHeight();
    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            outFile << mapData.GetTile(col, row) << ' ';
        }
        outFile << std::endl;
    }

    outFile.close();
}
