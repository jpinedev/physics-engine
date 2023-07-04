#ifndef __TILEMAPCOLLIDERCOMPONENT_HPP__
#define __TILEMAPCOLLIDERCOMPONENT_HPP__

#include <deque>
#include <iostream>
#include <memory>

#include "core/TilemapComponent.hpp"
#include "core/collision/ColliderComponent.hpp"
#include "core/resources/TilemapData.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif
/**
 * A collider for a tile on the tilemap
 */
class TilemapColliderComponent : public ColliderComponent
{
public:
    /**
     * Constructor for a TilemapColliderComponent
     */
    TilemapColliderComponent();
    /**
     * Destructor for a TilemapColliderComponent
     */
    virtual ~TilemapColliderComponent();

    virtual void Start() override;

    /**
     * Check if collider collides with anything else in the scene
     * @return If we collided with anything.
     */
    virtual bool RaycastColliderRectangle() override;

    virtual void GetBoundingBoxes(std::vector<Bounds>& out_bounds) override;

#ifdef GIZMOS
    virtual void DrawGizmos(RenderContext* renderer,
                            util::Gizmos* util) override;
#endif

protected:
    /**
     * If there is a null pointer then we search for the sprite render, if no
     * sprite renderer then we throw an error
     */
    void FindTilemapIfNull();

    /**
     * Does this collider collide with the given rectangle?
     * @param rect The rectangle we are checking collision with
     * @return True if there was a collision, else false
     */
    virtual bool CollidesWithRectangle(FRect* rect) override;

private:
    TilemapComponent* mTilemap = NULL;
    std::shared_ptr<TilemapData> mData;
};

#endif
