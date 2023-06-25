#ifndef __SPRITESHEETLOADER_HPP__
#define __SPRITESHEETLOADER_HPP__

#include "core/resources/ResourceLoader.hpp"
#include "core/resources/Spritesheet.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

/**
 * Load spritesheets from image files on the disk.
 *
 * Supports any image type that SDL_LoadBMP supports.
 */
class SpritesheetLoader : public ResourceLoader<Spritesheet>
{
public:
    /**
     * Clears the spritesheet loader
     */
    virtual ~SpritesheetLoader();

    /**
     * Load and parse the data from the file at fileLoc.
     * @param fileLoc The location of the loaded file
     */
    virtual void Load(std::string fileLoc) override;

private:
    // This class should only be instantiated by the ResourceManager.
    /**
     * Constructs a spritesheet loader with the given texture
     * @param textureLoader The texture we are loading for the spritesheet
     */
    SpritesheetLoader(ResourceLoader<SDL_Texture>* textureLoader);

    /**
     * A constructor that we do not want to be implemented
     */
    SpritesheetLoader() = delete;

    ResourceLoader<SDL_Texture>* mTextureLoader = NULL;

    friend class ResourceManager;
};

#endif
