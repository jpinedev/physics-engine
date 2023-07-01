#include "core/resources/TilemapLoader.hpp"
#include "core/resources/Spritesheet.hpp"
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

    TileLoc tileLoc{0, 0};
    while (file.good() && !file.eof())
    {
        std::getline(file, line);
        if (line.empty() || file.eof()) break;

        tileLoc.x = 0;
        std::stringstream ss(line);

        while (ss >> tile)
        {
            mapData.SetTile(tileLoc, tile);
            tileLoc.x++;
        }
        if (tileLoc.x < maxCols || (maxCols != 0 && tileLoc.x > maxCols))
        {
            throw std::invalid_argument(
                "Tilemap is jagged. Tilemaps must be rectangular.");
        }

        if (tileLoc.x > maxCols) maxCols = tileLoc.x;
        ++tileLoc.y;
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

    Size2D mapSize = mapData.GetSize();
    TileLoc tileLoc;
    for (tileLoc.y = 0; tileLoc.y < mapSize.y; ++tileLoc.y)
    {
        for (tileLoc.x = 0; tileLoc.x < mapSize.x; ++tileLoc.x)
        {
            outFile << mapData.GetTile(tileLoc) << ' ';
        }
        outFile << std::endl;
    }

    outFile.close();
}
