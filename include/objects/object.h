#ifndef OBJECT_H
#define OBJECT_H

#include <ray.h>
#include <intersection.h>
#include <limits>

class Object {
protected:
    Vec3f color;
public:
    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max()) = 0;
    virtual void printType() {
    }
};

class Plane : public Object {
protected:
    Vec3f point, normal;
    bool boolseye;
public:
    Plane(Vec3f point, Vec3f normal, Vec3f color, bool boolseye);
    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max());
    virtual void printType();
};

class Sphere : public Object {
private:
    Vec3f center;
    float radius;
public:
    Sphere(Vec3f center, float radius, Vec3f color);
    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max());
    virtual void printType();
};



#endif // OBJECT_H
