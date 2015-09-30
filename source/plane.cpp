#include <objects/object.h>

Plane::Plane(Vec3f point, Vec3f normal, Vec3f color, bool boolseye) {
    this->point = point;
    this->normal = normal;
    this->color = color;
    this->boolseye = boolseye;
}

bool Plane::intersect(const Ray &ray, Intersection &intersection) {
    float n, t, d;
    d = ray.direction.dotProduct(normal);

    if(d != 0) {
        n = (point - ray.origin).dotProduct(normal);
        t = n / d;
        if(t >= 0) {
            intersection.t = t;
            intersection.normal = normal;
            intersection.color = color;
            intersection.object = this;

            Vec3f intersectionPosition = ray.origin + ray.direction * t;

            if (std::fmod((intersectionPosition - point).length() * 0.25f, 1.0f) > 0.5f)
            {
                intersection.color *= 0.6f;
            }

            return true;
        }
    }

    return false;
}
