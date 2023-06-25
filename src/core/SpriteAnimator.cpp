#include "core/SpriteAnimator.hpp"
#include <iostream>
#include "core/SpriteRenderer.hpp"

SpriteAnimator::SpriteAnimator() : SpriteRenderer() {}

SpriteAnimator::~SpriteAnimator() {}

void SpriteAnimator::Receive(const std::string& message)
{
    if (mAnimations.count(message) > 0)
    {
        mActiveAnimation = mAnimations[message];
    }
}

void SpriteAnimator::Render(RenderContext* renderer)
{
    int spriteIndex =
        mActiveAnimation.spritesheetRow * mSpritesheet->GetSpritesheetCols() +
        (renderer->frameIdx / 12) % mActiveAnimation.frameCount;
    SetSpriteIndex(spriteIndex);
    SpriteRenderer::Render(renderer);
}

void SpriteAnimator::SetAnimation(const std::string& animName,
                                  unsigned int spritesheetRow,
                                  unsigned int frameCount)
{
    if (mAnimations.count(animName) > 0)
    {
        throw std::invalid_argument(
            "SpriteAnimator already has animation with that name");
    }

    mAnimations[animName] = {spritesheetRow, frameCount};
}
