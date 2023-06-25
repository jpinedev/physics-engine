#ifndef __TILEMAPLOADER_HPP__
#define __TILEMAPLOADER_HPP__

#include "core/resources/ResourceLoader.hpp"
#include "core/resources/TilemapData.hpp"

/**
 * Load a tilemap from a file on the disk.
 *
 * TODO: Document the file structure and extention of our tilemap file type.
 */
class TilemapLoader : public ResourceLoader<TilemapData>
{
public:
    /**
     * A destructor for Tile Map Loader
     */
    ~TilemapLoader();

    /**
     * Load and parse the data from the file at fileLoc.
     * @param fileLoc The location of the loaded file
     */
    virtual void Load(std::string fileLoc) override;

    /**
     * Save the data to the corresponding file (if implemented).
     * @param resource The place we are saving to
     */
    virtual void Save(std::shared_ptr<TilemapData>& resource) override;

private:
    // This class should only be instantiated by the ResourceManager.
    /**
     * Constructs a Tile Map Loader
     */
    TilemapLoader();

    friend class ResourceManager;
};

#endif
