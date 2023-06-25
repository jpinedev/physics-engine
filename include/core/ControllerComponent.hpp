#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#include "core/Component.hpp"
#include "core/UpdateContext.hpp"
/**
 * A player controller component for moving a character through the world.
 */
class ControllerComponent : public Component
{
public:
    /**
     * A constructor
     */
    ControllerComponent();

    /**
     * A destructor
     */
    virtual ~ControllerComponent();

    /**
     * An update loop for a component
     * @param update The update data that operates the update loop
     */
    virtual void Update(UpdateContext* update) override;

    /**
     * Sets the speed of this game object, the speed is default
     * if this is not called at all.
     *
     * @param val the speed to set to
     */
    void SetSpeed(float val);

private:
    float mMoveSpeed = 64.0f;
};

#endif
