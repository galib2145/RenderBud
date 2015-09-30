#include <objects/object.h>
#include <utils.h>
#include <cmath>

Sphere::Sphere(Vec3f center, float radius, Vec3f color) {
    this->center = center;
    this->radius = radius;
    this->color = color;
}

bool Sphere::intersect(const Ray &ray, Intersection &intersection) {
    float t0, t1;
    float radius2 = radius * radius;
    Vec3f L = ray.origin - this->center;
    float a = ray.direction.dotProduct(ray.direction);
    float b = 2 * ray.direction.dotProduct(L);
    float c = L.dotProduct(L) - radius2;

    if (!solveQuadratic(a, b, c, t0, t1))
        return false;

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }

    Vec3f hitPoint = ray.getPoint(t0);

    intersection.t = t0;
    intersection.color = color;
    intersection.point = hitPoint;
    intersection.normal = intersection.point - center;
    intersection.object = this;

    return true;
}
