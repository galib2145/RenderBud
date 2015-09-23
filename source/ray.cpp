#include <ray.h>

Ray::Ray(Vec3f &origin, Vec3f &direction) {
    this->origin = origin;
    this->direction = direction;
}
