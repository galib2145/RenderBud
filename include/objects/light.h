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

    Vec3f emitted() {
        return color * intensity;
    }

    virtual Vec3f shade(Intersection &intersection) = 0;
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

    virtual Vec3f shade(Intersection &intersection) {
        Vec3f lightDirection = position - intersection.position;
        lightDirection.normalize();
        float facingRatio = std::max(0.0f, intersection.normal.dotProduct(lightDirection));
        Vec3f currentColor = intersection.color * facingRatio * intensity * color;
        return currentColor;
    }
};

#endif // LIGHT_H
