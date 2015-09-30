#ifndef OBJECT_H
#define OBJECT_H

#include <ray.h>
#include <intersection.h>

class Object {
protected:
    Vec3f color;
public:
    virtual bool intersect(const Ray &ray, Intersection &intersection) = 0;
};

class Plane : public Object {
protected:
    Vec3f point, normal;
    bool boolseye;
public:
    Plane(Vec3f point, Vec3f normal, Vec3f color, bool boolseye);
    bool intersect(const Ray &ray, Intersection &intersection);
};

class Sphere : public Object {
private:
    Vec3f center;
    float radius;
public:
    Sphere(Vec3f center, float radius, Vec3f color);
    bool intersect(const Ray &ray, Intersection &intersection);
};



#endif // OBJECT_H
