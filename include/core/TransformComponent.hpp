#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "core/Component.hpp"
#include "core/TinyMath.hpp"

/**
 * The component that holds information on where a game object
 * is in world position, which can be observed, and modified.
 */
class TransformComponent : public Component
{
public:
    TransformComponent();
    virtual ~TransformComponent();

    /**
     * Returns the position of this transform.
     *
     * @return the Vec2D position of this transform
     */
    Vec2D GetPosition() const;

    /**
     * Sets the x and y position of this transform.
     *
     * @param x the x position to set
     * @param y the y position to set
     */
    void SetPosition(float x, float y);

    /**
     * Translates the x and y position of this transform.
     *
     * @param x position to translate
     * @param y position to translate
     */
    void TranslatePosition(float x, float y);

private:
    Vec2D mPosition;
};

#endif
