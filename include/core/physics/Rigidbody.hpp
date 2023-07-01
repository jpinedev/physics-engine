#ifndef PHYSICS_ENGINE_RIGIDBODY_H
#define PHYSICS_ENGINE_RIGIDBODY_H

#include <glm/vec2.hpp>
#include "core/Component.hpp"

namespace Physics
{

class Rigidbody : public Component
{
public:
    Rigidbody();
    virtual ~Rigidbody();

    virtual void Start() override;

private:
    glm::vec2 mPos{0, 0};
    glm::vec2 mVel{0, 0};
    glm::vec2 mAcc{0, 0};
};

}  // namespace Physics

#endif  // PHYSICS_ENGINE_RIGIDBODY_H
