#include <objects/object.h>

AABB::AABB(float minBound, float maxBound, Vec3f color) : m_minBound(minBound), m_maxBound(maxBound), Object(color) {
}


bool AABB::intersect(const Ray &ray, Intersection &intersection, float tNear) {
    float tmin = (m_minBound - ray.origin.x) / ray.direction.x;
    float tmax = (m_maxBound - ray.origin.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (m_minBound - ray.origin.y) / ray.direction.y;
    float tymax = (m_maxBound - ray.origin.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (m_minBound - ray.origin.z) / ray.direction.z;
    float tzmax = (m_maxBound - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    Vec3f hitPosition = ray.getPoint(tmin);
    return true;
}


void AABB::printType() {
}
