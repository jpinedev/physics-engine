#ifndef PHYSICS_ENGINE_RIGIDBODY_H
#define PHYSICS_ENGINE_RIGIDBODY_H

#include <glm/vec2.hpp>
#include "core/Component.hpp"
#include "core/UpdateContext.hpp"
#include "core/physics/PhysicsUpdateContext.hpp"
#include "core/util/Bounds.hpp"

class TransformComponent;
namespace Physics
{
class PhysicsEngine;
struct Hit2D;

class Rigidbody : public Component
{
public:
    Rigidbody(bool bIsStatic = false);
    virtual ~Rigidbody();

    virtual void Start() override;

    virtual void Update(UpdateContext* ctx) override;

    virtual void FixedUpdate(PhysicsUpdateContext const* ctx);

    void ResolveCollisions(const std::vector<Hit2D>& collisions);

    bool IsStatic() const { return mbIsStatic; }

    Bounds GetBoundingBox() const;
    glm::vec2 GetCenterOfMass() const { return mPos + mLocalCenterOfMass; }

    const glm::vec2& GetVelocity() { return mVel; }
    void SetVelocity(glm::vec2 vel) { mVel = vel; }
    const glm::vec2& GetPosition() { return mPos; }
    void SetPosition(glm::vec2 pos) { mPos = pos; }

private:
    void CalculateLocalBounds(const std::vector<Bounds>& allBounds);
    void CalculateLocalCenterOfMass();

private:
    PhysicsEngine* mpPhysicsEngine = NULL;
    TransformComponent* mpTransform = NULL;
    ColliderComponent* mpCollider = NULL;

    FRect mLocalBoundsRect;
    glm::vec2 mLocalCenterOfMass{0, 0};

    glm::vec2 mPos{0, 0};
    glm::vec2 mVel{0, 0};

    const bool mbIsStatic;
};

}  // namespace Physics

#endif  // PHYSICS_ENGINE_RIGIDBODY_H
