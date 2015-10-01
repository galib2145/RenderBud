#ifndef LIGHT_H
#define LIGHT_H

class Light : public Object {
public:
    Vec3f color;
    float intensity;
    Light(Vec3f color, float intensity) {
        this->color = color;
        this->intensity = intensity;
    }

    virtual bool intersect(const Ray &ray, Intersection &intersection) {
        return false;
    }
};

class PointLight : public Light {

public:
    Vec3f position;
    PointLight(Vec3f color, float intensity, Vec3f position) : Light(color, intensity) {
        this->position = position;
    }

    virtual bool intersect(const Ray &ray, Intersection &intersection) {
        return false;
    }
};

#endif // LIGHT_H
