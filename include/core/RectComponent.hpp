#ifndef __RECTCOMPONENT_HPP__
#define __RECTCOMPONENT_HPP__

#include "core/Component.hpp"
#include "core/RenderContext.hpp"
#include "core/TinyMath.hpp"

/**
 * Render a rectangle on the screen.
 *
 * Mostly useful for debugging.
 */
class RectComponent : public Component
{
public:
    /**
     * Constructor
     */
    RectComponent();

    /**
     * Destructor
     */
    virtual ~RectComponent();

    /**
     * A render loop for a component
     * @param renderer The render data that operates the render loop
     */
    virtual void Render(RenderContext* renderer) override;

    /**
     * Is the given rect intersecting with this rect
     * @param rect The rect we are checking
     * @return If we are intersecting or not
     */
    bool Intersects(const RectComponent& rect) const;

    /**
     * Size of the rect
     * @param w Width
     * @param h Height
     */
    void SetSize(float w, float h);

    /**
     * Sets the color of the rect
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    void SetColor(unsigned char r, unsigned char g, unsigned char b,
                  unsigned char a = 0xFF);

    /**
     * The size of the rect
     * @return The size of the rect
     */
    const Vec2D& size() const;

private:
    unsigned char mColor[4] = {0, 0, 0, 0xFF};
    Vec2D mSize = {1, 1};
};

#endif
