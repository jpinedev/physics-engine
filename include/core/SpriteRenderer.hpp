#ifndef SPRITE_H
#define SPRITE_H

#include <memory>
#include <string>

#include "core/Component.hpp"
#include "core/IGraphicsEngineRenderer.hpp"
#include "core/RenderContext.hpp"
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
    SpriteRenderer();
    virtual ~SpriteRenderer();

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
    inline void SetSpriteIndex(unsigned int index) { mSpriteIndex = index; }

    inline void SetSize(Size2D size)
    {
        mDest.w = size.x;
        mDest.h = size.y;
    }

    Size2D GetSize() { return Size2D{mDest.w, mDest.h}; }

private:
    unsigned int mSpriteIndex = 0;
    SDL_Rect mDest{0, 0, 0, 0};

protected:
    std::shared_ptr<Spritesheet> mSpritesheet = nullptr;
};

#endif
