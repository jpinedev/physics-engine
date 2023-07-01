#ifndef __SPRITECOLLIDERCOMPONENT_HPP__
#define __SPRITECOLLIDERCOMPONENT_HPP__

#include "core/Component.hpp"
#include "core/SpriteRenderer.hpp"
#include "core/collision/ColliderComponent.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

/**
 * A collider component for sprites
 */
class SpriteColliderComponent : public ColliderComponent
{
public:
    /**
     * Constructor for a SpriteColliderComponent
     */
    SpriteColliderComponent();

    /**
     * Destructor for a SpriteColliderComponent
     */
    virtual ~SpriteColliderComponent();

    /**
     * Check if collider collides with anything else in the scene
     * @return If we collided with anything.
     */
    virtual bool RaycastColliderRectangle() override;

#ifdef GIZMOS
    virtual void DrawGizmos(RenderContext* renderer,
                            util::Gizmos* util) override;
#endif

protected:
    /**
     * Does this collider collide with the given rectangle?
     * @param rect The rectangle we are checking collision with
     * @return True if there was a collision, else false
     */
    virtual bool CollidesWithRectangle(FRect* rect) override;

private:
    SpriteRenderer* mSpriteRenderer = NULL;

    /**
     * If there is a null pointer then we search for the sprite render, if no
     * sprite renderer then we throw an error
     */
    void FindSpriteRendererIfNull();

    /**
     * Gets the collider rectangle
     * @return The collider's rectangle hitbox
     */
    FRect GetCollisionRect();
};

#endif
