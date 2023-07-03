#ifndef __PHYSICSUPDATECONTEXT_HPP__
#define __PHYSICSUPDATECONTEXT_HPP__

#include <glm/vec2.hpp>

struct PhysicsUpdateContext {
    glm::vec2 gravity{0,0};
    const float kFixedTimestep;

    PhysicsUpdateContext(float timestep): kFixedTimestep(timestep) {}
};

#endif
