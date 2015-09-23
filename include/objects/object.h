#ifndef OBJECT_H
#define OBJECT_H

#include <ray.h>
#include <intersection.h>

class Object {
public:
    virtual bool intersect(const Ray &ray, Intersection &Intersection) = 0;
};


#endif // OBJECT_H
