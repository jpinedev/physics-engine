#include "core/physics/PhysicsEngine.hpp"

#include <chrono>
#include <csignal>
#include <unordered_map>
#include "core/Engine.hpp"
#include "core/physics/Rigidbody.hpp"
#include "core/util/SDLConversions.hpp"

#include <sys/signal.h>
#include <unistd.h>

namespace Physics
{
PhysicsEngine* PhysicsEngine::mpPhysicsEngine = NULL;

PhysicsEngine::PhysicsEngine(Engine* engine, float fixedTimestep)
    : mUpdateContext(fixedTimestep), mFixedTimestep(fixedTimestep)
{
    assert(mpPhysicsEngine == NULL);

    mpPhysicsEngine = this;
}

/*
void PhysicsEngine::RunPhysicsSimulation()
{
    mbShouldClose = false;
    mSubprocess = fork();
    if (mSubprocess) return;

    RunLoop();
}

void PhysicsEngine::Shutdown()
{
    mbShouldClose = true;
    //kill(mSubprocess, SIGKILL);
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
*/

void PhysicsEngine::FixedUpdate()
{
    typedef std::vector<Hit2D> HitArray;
    typedef std::unordered_map<Rigidbody*, HitArray> HitMap;

    HitMap hitMaps;
    Bounds overlap{glm::vec2{0, 0}};

    // TODO: split up into multiple jobs
    auto dbIt = mDynamicBodies.begin(), dbItEnd = mDynamicBodies.end();
    for (; dbIt != dbItEnd; ++dbIt)
    {
        for (StaticRigidbodyBoundsMap::reference staticBody : mStaticBodies)
        {
            for (auto& bounds : staticBody.second)
            {
                if (!bounds.GetOverlap((*dbIt)->GetBoundingBox(), &overlap))
                    continue;

                Hit2D hit = {overlap, true, staticBody.first};

                HitArray& hitMap = hitMaps[*dbIt];
                hitMap.emplace_back(hit);
                // TODO: Do I need to handle collisions on static bodies?
            }
        }
    }
    // TODO: join all threads

    // TODO: split up into multiple jobs
    dbIt = mDynamicBodies.begin();
    for (; dbIt != dbItEnd; ++dbIt)
    {
        if (!hitMaps.count(*dbIt)) continue;

        (*dbIt)->ResolveCollisions(hitMaps[*dbIt]);
    }
    // TODO: join all threads

    dbIt = mDynamicBodies.begin();
    for (; dbIt != dbItEnd; ++dbIt)
    {
        (*dbIt)->FixedUpdate(&mUpdateContext);
    }
}

}  // namespace Physics
