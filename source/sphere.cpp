#include <objects/sphere.h>
#include <utils.h>

Sphere::Sphere(Vec3f &center, float radius) {
    this->center = center;
    this->radius = radius;
}

bool Sphere::intersect(const Ray &ray, Intersection &intersection) {
    float t0, t1;
    Vec3f L = ray.origin - this->center;
    float a = ray.direction.dotProduct(ray.direction);
    float b = 2 * ray.direction.dotProduct(L);
    float c = L.dotProduct(L) - this->radius;

    if (!solveQuadratic(a, b, c, t0, t1))
        return false;

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }

    intersection.t = t0;
    intersection.color = Vec3f(1, 0, 1);
    intersection.normal = Vec3f(0,0,0);
    intersection.object = this;

    return true;
}
