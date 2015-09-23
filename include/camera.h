#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "geometry.h"
#include "utils.h"

class Camera {
public:
    float fieldOfView;
    Matrix44f worldToCamera;
    float scalingFactor;

    Camera() {
    }

    Camera(float fieldOfView, const Matrix44f &worldToCamera) {
        this->fieldOfView = fieldOfView;
        this->worldToCamera = worldToCamera;
        this->scalingFactor = tan(degreeToRadian(fieldOfView) * 0.5);
    }
};


#endif // CAMERA_H
