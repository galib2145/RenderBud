#ifndef RAY_H
#define RAY_H

#include <geometry.h>

class Ray {
public:
    Vec3f origin, direction;
    Ray(Vec3f &origin, Vec3f &direction);
    Vec3f getPoint(float t) const;
};

#endif // RAY_H
