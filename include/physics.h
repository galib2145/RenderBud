#ifndef PHYSICS_H
#define PHYSICS_H

#include <geometry.h>

enum MaterialType {
    kDiffuse,
    kReflection,
    kReflectionAndRefraction
};

Vec3f reflect(const Vec3f &I, const Vec3f &N);
bool refract(const Vec3f &incidentDirection, const Vec3f &normal, float refractiveIndex, Vec3f &refractionDirection);
void fresnel(const Vec3f &incidentDirection, const Vec3f &normal, const float &refractiveIndex, float &kr);

#endif // PHYSICS_H
