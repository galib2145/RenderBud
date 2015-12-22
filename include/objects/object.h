#ifndef OBJECT_H
#define OBJECT_H

#include <ray.h>
#include <intersection.h>
#include <limits>
#include <physics.h>

class Object {
protected:
    Vec3f color;
public:
    float m_reflectance = 0;
    float m_refractiveIndex = 0;
    int id;

    Object() {
    }

    Object(Vec3f color) {
        this->color = color;
    }

    Object(float reflectance, float refractiveIndex) : m_reflectance(reflectance), m_refractiveIndex(refractiveIndex) {
    }

    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max()) = 0;
    virtual void printType() {
    }

    virtual bool sampleSurface(float u1,
                               float u2,
                               const Vec3f& referencePosition,
                               Vec3f& surfacePosition,
                               Vec3f& surfaceNormal) {
        return false;
    }
};

class Plane : public Object {
protected:
    Vec3f point, normal;
    bool boolseye;
public:
    Plane(Vec3f point, Vec3f normal, Vec3f color, float reflectance = 0);
    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max());
    virtual void printType();
};

class AABB : public Object {
protected:
    float m_minBound, m_maxBound;
public:
    AABB(float minBound, float maxBound, Vec3f color);
    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max());
    virtual void printType();
};

class Sphere : public Object {
private:
    Vec3f center;
    float radius;
public:
    Sphere(Vec3f center, float radius, Vec3f color, int id, float reflectance = 0, float refractiveIndex = 0);
    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max());
    virtual void printType();
};



#endif // OBJECT_H
