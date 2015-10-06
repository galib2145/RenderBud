#ifndef LIGHT_H
#define LIGHT_H

#include <geometry.h>
#include <cmath>

class Light : public Object {
public:
    Vec3f color;
    float intensity;
    Light(Vec3f color, float intensity) {
        this->color = color;
        this->intensity = intensity;
    }

    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max()) {
        return false;
    }

    Vec3f emitted() {
        return color * intensity;
    }

    virtual Vec3f getDirection(Intersection &intersection, float &distance) = 0;
    virtual Vec3f getLightEnergy(Intersection &intersection) = 0;
};

class PointLight : public Light {

public:
    Vec3f position;
    PointLight(Vec3f color, float intensity, Vec3f position) : Light(color, intensity) {
        this->position = position;
    }

    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max() ) {
        return false;
    }

    virtual Vec3f getDirection(Intersection &intersection, float &distance) {
        Vec3f direction = position - intersection.position;
        distance = sqrtf(direction.norm());
        direction /= distance;
        return direction;
    }

    virtual Vec3f getLightEnergy(Intersection &intersection) {
        float r2 = (position - intersection.position).norm();
        Vec3f totalEnergy = color * intensity;
        totalEnergy /= M_PI;
        return totalEnergy;
    }
};


#endif // LIGHT_H
