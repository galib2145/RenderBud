#ifndef LIGHT_H
#define LIGHT_H

class Light {
public:
    Vec3f color;
    float intensity;
    Light(Vec3f color, float intensity) {
        this->color = color;
        this->intensity = intensity;
    }
};

class PointLight : public Light {

public:
    Vec3f position;
    PointLight(Vec3f color, float intensity, Vec3f position) : Light(color, intensity) {
        this->position = position;
    }
};

#endif // LIGHT_H
