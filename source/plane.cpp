#include <objects/object.h>

Plane::Plane(Vec3f point, Vec3f normal, Vec3f color, float reflectance) {
    this->point = point;
    this->normal = normal;
    this->color = color;
    this->boolseye = boolseye;
    this->m_reflectance = reflectance;
}

bool Plane::intersect(const Ray &ray, Intersection &intersection, float tNear) {
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
            intersection.position = ray.origin + ray.direction * t;

            return true;
        }
    }

    return false;
}


void Plane::printType() {
    std::cout << "I am a plane" << std::endl;
}
