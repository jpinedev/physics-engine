#ifndef __PHYSICS_ENGING_HPP__
#define __PHYSICS_ENGING_HPP__

#include <pthread.h>
#include <cassert>
#include <set>
#include <thread>
#include <unordered_map>
#include <vector>

#include "core/Engine.hpp"
#include "core/physics/PhysicsUpdateContext.hpp"
#include "core/physics/Rigidbody.hpp"
#include "core/util/Bounds.hpp"

class ColliderComponent;

namespace Physics
{
class Rigidbody;

struct Hit2D
{
    Bounds bounds;
    bool bHitStatic;
    Rigidbody* pRigidbody;
};

class PhysicsEngine
{
public:
    PhysicsEngine(Engine* engine, float fixedTimestep);
    PhysicsEngine(const PhysicsEngine&) = delete;
    ~PhysicsEngine() { mpPhysicsEngine = NULL; }
    static PhysicsEngine* Instance() { return mpPhysicsEngine; }

public:
    void AddStaticColliders(Rigidbody* rb, const std::vector<Bounds>& bounds)
    {
        assert(rb->IsStatic());
        mStaticBodies.emplace(rb, bounds);
    }
    void AddDynamicBody(Rigidbody* rb)
    {
        assert(!rb->IsStatic());
        mDynamicBodies.insert(rb);
    }

    void SetGravity(glm::vec2 gravity) { mUpdateContext.gravity = gravity; }

    void RunPhysicsSimulation();

    void Shutdown();

private:
    void RunLoop();
    void FixedUpdate();

private:
    static PhysicsEngine* mpPhysicsEngine;
    Engine* mpEngine = NULL;

    std::thread mThread;

    std::unordered_map<Rigidbody*, const std::vector<Bounds>> mStaticBodies;
    std::set<Rigidbody*> mDynamicBodies;

    PhysicsUpdateContext mUpdateContext;
    std::chrono::duration<float> mFixedTimestep;

    bool mbShouldClose{false};
};

}  // namespace Physics

#endif  // __PHYSICS_ENGING_HPP__
