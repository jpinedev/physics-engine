#ifndef __RECTCOMPONENT_HPP__
#define __RECTCOMPONENT_HPP__

#include <glm/vec2.hpp>
#include "core/Component.hpp"
#include "core/RenderContext.hpp"

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

    inline void SetSize(glm::vec2 size) { mSize = size; }

    inline void SetColor(unsigned char r, unsigned char g, unsigned char b,
                         unsigned char a = 0xFF);

    const glm::vec2& GetSize() const { return mSize; }

private:
    unsigned char mColor[4] = {0, 0, 0, 0xFF};
    glm::vec2 mSize{1, 1};
};

#endif
