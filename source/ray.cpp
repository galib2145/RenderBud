#include <ray.h>

Ray::Ray(Vec3f &origin, Vec3f &direction, RayType rayType) {
    this->origin = origin;
    this->direction = direction;
    this->rayType = rayType;
}

Vec3f Ray::getPoint(float t) const {
    return origin + direction * t;
}
