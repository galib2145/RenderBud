#include <ray.h>

Ray::Ray(Vec3f &origin, Vec3f &direction) {
    this->origin = origin;
    this->direction = direction;
}

Vec3f Ray::getPoint(float t) const {
    return origin + direction * t;
}
