#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <ray.h>
#include <geometry.h>

class Object;

class Intersection {
public:
   Vec3f color;
   Vec3f normal;
   float t;
   Vec3f position;
   Object* object;
   Vec3f emitted;

   Intersection() {
   }

   Intersection(Vec3f &color, Vec3f &normal, Vec3f &position, float &t, Object* object) {
        this->color = color;
        this->normal = normal;
        this->t = t;
        this->position = position;
        this->object = object;
   }
};

#endif // INTERSECTION_H
