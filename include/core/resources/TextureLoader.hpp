#ifndef __TEXTURELOADER_HPP__
#define __TEXTURELOADER_HPP__

#include "core/resources/ResourceLoader.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

/**
 * Load textures from image files on the disk.
 *
 * Supports any image type that SDL_LoadBMP supports.
 */
class TextureLoader : public ResourceLoader<SDL_Texture>
{
public:
    /**
     * A destructor for Texture Loader
     */
    virtual ~TextureLoader();

    /**
     * Load and parse the data from the file at fileLoc.
     * @param fileLoc The location of the loaded file
     */
    virtual void Load(std::string fileLoc) override;

private:
    // This class should only be instantiated by the ResourceManager.
    /**
     * Constructs a texture loader with the given renderer
     * @param renderer The renderer that is used to load the texture
     */
    TextureLoader(SDL_Renderer* renderer);
    /**
     * A constructor that we do not want to be implemented
     */
    TextureLoader() = delete;

    SDL_Renderer* mRenderer = NULL;

    friend class ResourceManager;
};

#endif
