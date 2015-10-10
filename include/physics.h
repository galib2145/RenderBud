#ifndef PHYSICS_H
#define PHYSICS_H

#include <geometry.h>

enum MaterialType {
    kDiffuse,
    kReflection,
    kReflectionAndRefraction
};

Vec3f reflect(const Vec3f &I, const Vec3f &N);

#endif // PHYSICS_H
