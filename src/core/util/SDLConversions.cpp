#include "core/util/SDLConversions.hpp"

bool HasIntersection(FRect lhs, FRect rhs)
{
    return (lhs.x < rhs.x + rhs.w && lhs.x + lhs.w > rhs.x &&
            lhs.y < rhs.y + rhs.h && lhs.y + lhs.h > rhs.y);
}
