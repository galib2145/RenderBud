#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <ray.h>
#include <geometry.h>
#include <objects/object.h>

class Object;

class Intersection {
public:
   Vec3f color;
   Vec3f normal;
   float t;
   Object* object;

   Intersection() {
   }

   Intersection(Vec3f &color, Vec3f &normal, float &t, Object* object) {
        this->color = color;
        this->normal = normal;
        this->t = t;
        this->object = object;
   }
};

#endif // INTERSECTION_H
