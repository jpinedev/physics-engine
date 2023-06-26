#ifndef __COLLIDER_HPP__
#define __COLLIDER_HPP__

#include <iostream>

#include "core/Component.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

/**
 * This checks the collision state for tiles and assets
 */
class ColliderComponent : public Component
{
public:
    /**
     * Constructor for a Collider
     */
    ColliderComponent();
    /**
     * Destructor for a Collider
     */
    virtual ~ColliderComponent(){};

    /**
     * Checks if the collider is colliding with another collider
     * @param rect The rectangle we are checking against
     * @return If we collided or not
     */
    virtual bool CheckCollisionWithRectangle(SDL_Rect* rect);

    /**
     * Check if collider collides with anything else in the scene
     * @return If we collided with anything.
     */
    virtual bool RaycastColliderRectangle() = 0;

    /**
     * Sets whether this collider is a collider or trigger
     * @param isTrigger If true, then this is a trigger, if false it is a
     * collider
     */
    virtual void SetIsTrigger(bool isTrigger);

#ifdef GIZMOS
    virtual void DrawGizmos(RenderContext* renderer,
                            util::Gizmos* util) override = 0;
#endif

protected:
    /**
     * Does this collider collide with the given rectangle?
     * @param rect The rectangle we are checking collision with
     * @return True if there was a collision, else false
     */
    virtual bool CollidesWithRectangle(SDL_Rect* rect) = 0;

private:
    bool mIsTrigger = false;
};

#endif
