#include <physics.h>
Vec3f reflect(const Vec3f &I, const Vec3f &N)
{
    return I - 2 * I.dotProduct(N) * N;
}
