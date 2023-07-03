#ifndef PHYSICS_ENGINE_RIGIDBODY_H
#define PHYSICS_ENGINE_RIGIDBODY_H

#include <glm/vec2.hpp>
#include "core/Component.hpp"
#include "core/UpdateContext.hpp"
#include "core/physics/PhysicsUpdateContext.hpp"
#include "core/util/Bounds.hpp"

namespace Physics
{
class PhysicsEngine;
struct Hit2D;

class Rigidbody : public Component
{
public:
    Rigidbody(bool bIsStatic);
    virtual ~Rigidbody();

    virtual void Start() override;

    virtual void Update(UpdateContext* ctx) override;

    virtual void FixedUpdate(PhysicsUpdateContext* ctx);

    void ResolveCollisions(const std::vector<Hit2D>& collisions);

    bool IsStatic() const { return mbIsStatic; }

    Bounds GetBoundingBox() const;

private:
    PhysicsEngine* mpPhysicsEngine = NULL;

    glm::vec2 mPos{0, 0};
    glm::vec2 mVel{0, 0};

    const bool mbIsStatic;
};

}  // namespace Physics

#endif  // PHYSICS_ENGINE_RIGIDBODY_H
