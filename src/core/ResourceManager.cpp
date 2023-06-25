#include "core/ResourceManager.hpp"
#include "core/resources/Spritesheet.hpp"
#include "core/resources/SpritesheetLoader.hpp"
#include "core/resources/TextureLoader.hpp"
#include "core/resources/TilemapLoader.hpp"

#include <iostream>

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

ResourceManager& ResourceManager::instance()
{
    static ResourceManager* _instance = new ResourceManager();
    return *_instance;
}

int ResourceManager::Startup(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    return 0;
}
int ResourceManager::Shutdown()
{
    // Free any instantiated loaders

    if (mTextureLoader)
    {
        delete mTextureLoader;
    }

    if (mTilemapLoader)
    {
        delete mTilemapLoader;
    }

    if (mSpritesheetLoader)
    {
        delete mSpritesheetLoader;
    }

    return 0;
}

ResourceLoader<SDL_Texture>* ResourceManager::Textures()
{
    if (!mTextureLoader)
    {
        mTextureLoader = new TextureLoader(mRenderer);
    }

    return mTextureLoader;
}
ResourceLoader<TilemapData>* ResourceManager::Tilemaps()
{
    if (!mTilemapLoader)
    {
        mTilemapLoader = new TilemapLoader();
    }

    return mTilemapLoader;
}
ResourceLoader<Spritesheet>* ResourceManager::Spritesheets()
{
    if (!mSpritesheetLoader)
    {
        mSpritesheetLoader = new SpritesheetLoader(Textures());
    }

    return mSpritesheetLoader;
}
