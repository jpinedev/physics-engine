#include "core/resources/SpritesheetLoader.hpp"
#include "core/resources/Spritesheet.hpp"

#include <memory>
#include <stdexcept>

SpritesheetLoader::SpritesheetLoader(ResourceLoader<SDL_Texture>* textureLoader)
{
    if (!textureLoader)
    {
        throw std::invalid_argument(
            "Tried to initialize sprite loader without valid texture loader "
            "instance.");
    }
    mTextureLoader = textureLoader;
}

SpritesheetLoader::~SpritesheetLoader() {}

void SpritesheetLoader::Load(std::string fileLoc)
{
    if (mResources.count(fileLoc) != 0) return;

    mTextureLoader->Load(fileLoc);

    std::shared_ptr<SDL_Texture> texture = mTextureLoader->Get(fileLoc);

    Spritesheet* spritesheet = new Spritesheet(texture);
    std::shared_ptr<Spritesheet> spritesheetResource(spritesheet);

    mResources.emplace(fileLoc, std::move(spritesheetResource));
}
