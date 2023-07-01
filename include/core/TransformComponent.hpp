#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/vec2.hpp>
#include "core/Component.hpp"

/**
 * The component that holds information on where a game object
 * is in world position, which can be observed, and modified.
 */
class TransformComponent : public Component
{
public:
    TransformComponent();
    virtual ~TransformComponent();

    glm::vec2 GetPosition() const { return mPosition; }

    inline void SetPosition(float x, float y) { SetPosition(x, y); }
    inline void SetPosition(glm::vec2 pos) { mPosition = pos; }
    inline void TranslatePosition(float x, float y)
    {
        TranslatePosition({x, y});
    }
    inline void TranslatePosition(glm::vec2 translate)
    {
        mPosition += translate;
    }

private:
    glm::vec2 mPosition{0, 0};
};

#endif
