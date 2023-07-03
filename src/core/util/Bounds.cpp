#include "core/util/Bounds.hpp"

Bounds::Bounds(std::initializer_list<glm::vec2> toContain) noexcept
{
    if (toContain.size() == 0) return;

    auto pointIt = toContain.begin(), pointItEnd = toContain.end();

    min = max = *pointIt;
    ++pointIt;

    for (; pointIt != pointItEnd; ++pointIt)
    {
        left = glm::min(left, pointIt->x);
        top = glm::min(top, pointIt->y);
        right = glm::max(right, pointIt->x);
        bottom = glm::min(bottom, pointIt->y);
    }

    mbInitialized = true;
}

Bounds::Bounds(std::initializer_list<Bounds> toContain) noexcept
{
    if (toContain.size() == 0) return;

    for (auto boundIt = toContain.begin(), boundItEnd = toContain.end();
         boundIt != boundItEnd; ++boundIt)
    {
        if (!boundIt->mbInitialized) continue;

        if (!mbInitialized)
        {
            *this = *boundIt;
            mbInitialized = true;
            continue;
        }

        left = glm::min(left, boundIt->left);
        top = glm::min(top, boundIt->top);
        right = glm::max(right, boundIt->right);
        bottom = glm::min(bottom, boundIt->bottom);
    }
}

bool Bounds::GetOverlap(const Bounds& other, Bounds* out_overlap) const
{
    if (left > other.right || top > other.bottom || right < other.left ||
        bottom < other.top)
        return false;

    if (!out_overlap) return true;

    out_overlap->left = glm::max(left, other.left);
    out_overlap->top = glm::max(top, other.top);
    out_overlap->left = glm::min(right, other.right);
    out_overlap->left = glm::min(bottom, other.bottom);
    return true;
}
