#ifndef SPHERE_H
#define SPHERE_H

#include <objects/object.h>
#include <intersection.h>

class Sphere : public Object {
private:
    Vec3f center;
    float radius;
public:
    Sphere(Vec3f &center, float radius);
    bool intersect(const Ray &ray, Intersection &intersection);
};

#endif // SPHERE_H
