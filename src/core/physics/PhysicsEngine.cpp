#include "core/physics/PhysicsEngine.hpp"

#include <chrono>
#include <thread>
#include <unordered_map>
#include "core/physics/Rigidbody.hpp"
#include "core/util/SDLConversions.hpp"

namespace Physics
{
PhysicsEngine* PhysicsEngine::mpPhysicsEngine = NULL;

PhysicsEngine::PhysicsEngine(Engine* engine, float fixedTimestep)
    : mUpdateContext(fixedTimestep), mFixedTimestep(fixedTimestep)
{
    assert(mpPhysicsEngine == NULL);

    mpPhysicsEngine = this;
}

void PhysicsEngine::RunPhysicsSimulation()
{
    mbShouldClose = false;
    mThread = std::thread(&PhysicsEngine::RunLoop, *this);
}

void PhysicsEngine::Shutdown()
{
    mbShouldClose = true;
    mThread.join();
}

void PhysicsEngine::RunLoop()
{
    namespace chrono = std::chrono;
    auto updateStartTime = chrono::high_resolution_clock::now();
    chrono::duration<float> frameTime;

    while (!mbShouldClose)
    {
        updateStartTime = chrono::high_resolution_clock::now();
        FixedUpdate();

        std::this_thread::sleep_until(updateStartTime + mFixedTimestep);
        std::cout << "Physics update.\n";
    }
}

void PhysicsEngine::FixedUpdate()
{
    std::unordered_map<Rigidbody*, std::unordered_map<Rigidbody*, Hit2D>>
        hitMap;
    Bounds overlap{glm::vec2{0,0}};

    auto dbIt = mDynamicBodies.begin(), dbItEnd = mDynamicBodies.end();
    for (; dbIt != dbItEnd; ++dbIt)
    {
        for (auto staticBody : mStaticBodies)
        {
            for (auto bounds : staticBody.second)
            {
                if (!bounds.GetOverlap((*dbIt)->GetBoundingBox(), &overlap))
                    continue;
            }
        }
    }
}

}  // namespace Physics
