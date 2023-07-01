#ifndef __COLLISION_HANDLER_HPP__
#define __COLLISION_HANDLER_HPP__

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

namespace
{
class ColliderComponent;
class RectCollider;
}  // namespace

namespace physics
{

struct Collision
{
    ColliderComponent* collider;
    SDL_Rect overlap;
};

class IRectCollisionHandler
{
public:
    virtual Collision* CheckCollision(RectCollider* rect,
                                      ColliderComponent* collider) = 0;
};

class CollisionHandler : public IRectCollisionHandler
{
public:  // CollisionHandler
    Collision* CheckCollision(RectCollider* rect1, RectCollider* rect2);

public:  // IRectCollisionHandler
    virtual Collision* CheckCollision(RectCollider* rect,
                                      ColliderComponent* collider) = 0;
};

}  // namespace physics

#endif  // __COLLISION_HANDLER_HPP__
