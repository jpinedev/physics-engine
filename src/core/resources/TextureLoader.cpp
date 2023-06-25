#include "core/resources/TextureLoader.hpp"

#include <iostream>
#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

TextureLoader::TextureLoader(SDL_Renderer* renderer) { mRenderer = renderer; }
TextureLoader::~TextureLoader() {}

void TextureLoader::Load(std::string fileLoc)
{
    if (mResources.count(fileLoc) != 0) return;

    SDL_Surface* surface = SDL_LoadBMP(fileLoc.c_str());

    if (surface == nullptr)
    {
        std::cerr << fileLoc << " not found!\n";
    }
    else
    {
        std::cout << "SDL_LoadBMP allocated\n";
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);

    if (nullptr == texture)
    {
        std::cerr << "Error creating texture\n";
    }
    else
    {
        std::cout << "SDL_Texture allocated\n";
    }

    std::cout << "New copy of " << fileLoc << " has been loaded\n";
    std::shared_ptr<SDL_Texture> textureResource(
        texture,
        [fileLoc](auto texPtr)
        {
            std::cout << "Destroying texture '" << fileLoc << "'...\n";
            SDL_DestroyTexture(texPtr);
        });
    mResources.emplace(fileLoc, textureResource);

    SDL_FreeSurface(surface);
    std::cout << "SDL_LoadBMP freed\n";
}
