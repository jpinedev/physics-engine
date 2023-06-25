#ifndef SPRITE_H
#define SPRITE_H

#include <memory>
#include <string>

#include "core/Component.hpp"
#include "core/IGraphicsEngineRenderer.hpp"
#include "core/RenderContext.hpp"
#include "core/TinyMath.hpp"
#include "core/TransformComponent.hpp"
#include "core/UpdateContext.hpp"
#include "core/resources/Spritesheet.hpp"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class SpriteRenderer : public Component
{
public:
    /**
     * Constructor
     */
    SpriteRenderer();
    /**
     * Destructor
     */
    virtual ~SpriteRenderer();

    /**
     * Render the sprite
     * @param ren The renderer data we are using
     */
    virtual void Render(RenderContext* ren) override;

    /**
     * Load a spritesheet
     * @param spritesheet The spritesheet we are using
     */
    void UseSpritesheet(std::shared_ptr<Spritesheet> spritesheet);

    /**
     * Set the index of the sprite on the spritsheet to render
     * @param index The index of the sprite
     */
    void SetSpriteIndex(unsigned int index);

    /**
     * Set the display size of the sprite in the game
     * @param width Width
     * @param height Height
     */
    void SetDisplaySize(unsigned int width, unsigned int height);

    /**
     * Gets the dimensions of the sprite
     * @return The dimensions of the sprite
     */
    SDL_Rect GetDisplayDimensions();

private:
    unsigned int mSpriteIndex = 0;
    SDL_Rect mDest{0, 0, 0, 0};

protected:
    std::shared_ptr<Spritesheet> mSpritesheet = nullptr;
};

#endif
