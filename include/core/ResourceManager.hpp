#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

#include "core/resources/ResourceLoader.hpp"
#include "core/resources/Spritesheet.hpp"
#include "core/resources/SpritesheetLoader.hpp"
#include "core/resources/TextureLoader.hpp"
#include "core/resources/TilemapLoader.hpp"

/**
 * Resource manager is a singleton that should be initialized with
 * instance().StartUp and destroyed with instance.ShutDown.
 *
 * TODO: Add support for audio files, fonts, tilemap levels, and spritesheets
 * (?).
 */
class ResourceManager
{
public:
    /**
     * Get reference to the Singleton instance
     * @return A reference to the singleton instance
     */
    static ResourceManager& instance();

    /**
     * Destructor
     * In theory, this is never called
     */
    ~ResourceManager();

    /**
     * Starts up the Resource Manager
     * @param renderer The renderer we are using
     * @return 0 if it worked
     */
    int Startup(SDL_Renderer* renderer);

    /**
     * Shuts down the Resource Manager
     * @return 0 if it worked
     */
    int Shutdown();

    // Expose the resource loaders for use on the singleton instance.
    // Create the loader if it doesn't already exist.

    /**
     * Gets the textures
     * @return The textures
     */
    ResourceLoader<SDL_Texture>* Textures();

    /**
     * Gets the tile maps
     * @return The tile maps
     */
    ResourceLoader<TilemapData>* Tilemaps();

    /**
     * Gets the spritesheets
     * @return The spritesheets
     */
    ResourceLoader<Spritesheet>* Spritesheets();

private:
    // Hide the constructor to be used as a singleton
    /**
     * Constructor
     */
    ResourceManager();

    SDL_Renderer* mRenderer = NULL;

    // All loaders should be stored here:
    TextureLoader* mTextureLoader = NULL;
    TilemapLoader* mTilemapLoader = NULL;
    SpritesheetLoader* mSpritesheetLoader = NULL;
};

#endif
