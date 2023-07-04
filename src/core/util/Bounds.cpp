#include "core/util/Bounds.hpp"
#include <stdexcept>

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
        bottom = glm::max(bottom, pointIt->y);
    }

    assert(left <= right);
    assert(top <= bottom);
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
        bottom = glm::max(bottom, boundIt->bottom);
    }

    assert(!mbInitialized || left <= right);
    assert(!mbInitialized || top <= bottom);
}

bool Bounds::GetOverlap(const Bounds& other, Bounds* out_overlap) const
{
    if (!mbInitialized || !other.mbInitialized)
        throw std::runtime_error("Overlap of undefined bounds does not exist.");

    if (left > other.right || top > other.bottom || right < other.left ||
        bottom < other.top)
        return false;

    if (!out_overlap) return true;

    out_overlap->left = glm::max(left, other.left);
    out_overlap->top = glm::max(top, other.top);
    out_overlap->right = glm::min(right, other.right);
    out_overlap->bottom = glm::min(bottom, other.bottom);

    assert(out_overlap->left <= out_overlap->right);
    assert(out_overlap->top <= out_overlap->bottom);
    return true;
}

Bounds& Bounds::Union(const Bounds& other)
{
    if (!mbInitialized || !other.mbInitialized)
        throw std::runtime_error("Union of undefined bounds does not exist.");

    left = glm::min(left, other.left);
    top = glm::min(top, other.top);
    right = glm::max(right, other.right);
    bottom = glm::max(bottom, other.bottom);

    assert(left <= right);
    assert(top <= bottom);
    return *this;
}
