#ifndef SPRITEANIMATOR_HPP
#define SPRITEANIMATOR_HPP

#include <iostream>
#include <memory>
#include <unordered_map>

#include "core/Component.hpp"
#include "core/RenderContext.hpp"
#include "core/SpriteRenderer.hpp"
#include "core/resources/Spritesheet.hpp"

struct Animation
{
    unsigned int spritesheetRow;
    unsigned int frameCount;
};

/**
 * A SpriteAnimator to cycle through the walking direction animations.
 */
class SpriteAnimator : public SpriteRenderer
{
public:
    /**
     * Constructor
     */
    SpriteAnimator();
    /**
     * Destructor
     */
    virtual ~SpriteAnimator();
    /**
     * Render the sprite
     */
    virtual void Render(RenderContext* render) override;
    /**
     * Receive the broadcasted message
     */
    virtual void Receive(const std::string& message) override;

    void SetAnimation(const std::string& animName, unsigned int spritesheetRow,
                      unsigned int frameCount);

private:
    Animation mActiveAnimation{0, 0};
    std::unordered_map<std::string, Animation> mAnimations;
};

#endif
