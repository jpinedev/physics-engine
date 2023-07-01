#include "core/RectComponent.hpp"
#include "core/Component.hpp"
#include "core/GameObject.hpp"
#include "core/RenderContext.hpp"
#include "core/TransformComponent.hpp"

RectComponent::RectComponent() : Component("rect") {}
RectComponent::~RectComponent() {}

void RectComponent::Render(RenderContext* renderer)
{
    const auto& pos = mGameObject->GetTransform().GetPosition();
    SDL_Rect fillRect = {(int)pos.x, (int)pos.y, (int)mSize.x, (int)mSize.y};

    SDL_SetRenderDrawColor(renderer->renderer, mColor[0], mColor[1], mColor[2],
                           mColor[3]);
    SDL_RenderFillRect(renderer->renderer, &fillRect);
}

bool RectComponent::Intersects(const RectComponent& rect) const
{
    const auto& thisPos = mGameObject->GetTransform().GetPosition();
    const auto& rectPos = rect.mGameObject->GetTransform().GetPosition();

    if (thisPos.x + mSize.x < rectPos.x) return false;
    if (thisPos.y + mSize.y < rectPos.y) return false;
    if (rectPos.x + rect.mSize.x < thisPos.x) return false;
    if (rectPos.y + rect.mSize.y < thisPos.y) return false;
    return true;
}

void RectComponent::SetColor(unsigned char r, unsigned char g, unsigned char b,
                             unsigned char a)
{
    mColor[0] = r;
    mColor[1] = g;
    mColor[2] = b;
    mColor[3] = a;
}
