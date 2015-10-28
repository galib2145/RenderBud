#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "geometry.h"
#include "utils.h"
#include "ray.h"

class Camera {
public:
    float fieldOfView;
    Matrix44f worldToCamera;
    float scalingFactor;
    Vec3f origin, target, targetUpDirection;

    Camera() {
    }

    Camera(float fieldOfView, const Matrix44f &worldToCamera) {
        this->fieldOfView = fieldOfView;
        this->worldToCamera = worldToCamera;
        this->scalingFactor = tan(degreeToRadian(fieldOfView) * 0.5);
    }

    Camera(float fieldOfView, Vec3f origin, Vec3f target, Vec3f targetUpDirection) {
        this->fieldOfView = fieldOfView;
        this->targetUpDirection = targetUpDirection;
        this->origin = origin;
        this->target = target;
    }

    Ray makeRay(float x, float y) {
        Vec3f forward = (target - origin).normalize();
        Vec3f right = forward.crossProduct(targetUpDirection).normalize();
        Vec3f up = right.crossProduct(forward).normalize();
        float tanFov = tan(degreeToRadian(fieldOfView));

        Vec3f rayOrigin = origin;
        Vec3f rayDirection = forward +
                             right * ((x - 0.5f) * tanFov) +
                             up * ((y - 0.5f) * tanFov);
        rayDirection.normalize();

        Ray ray(rayOrigin, rayDirection);

        return ray;
    }
};


#endif // CAMERA_H
