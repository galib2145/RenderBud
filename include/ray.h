#ifndef RAY_H
#define RAY_H

#include <geometry.h>

enum RayType {
    kPrimaryRay,
    kShadowRay
};

class Ray {
public:
    Vec3f origin, direction;
    RayType rayType;
    Ray(Vec3f &origin, Vec3f &direction, RayType rayType = kPrimaryRay);
    Vec3f getPoint(float t) const;
};

#endif // RAY_H
