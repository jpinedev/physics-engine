#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include <set>

class ColliderComponent;

class Physics
{
public:
private:
    std::vector<Rigidbody> mColliders;
    std::vector<ColliderComponent> mStaticColliders;
};

#endif  // __PHYSICS_HPP__
