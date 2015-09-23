#ifndef TRACER_H
#define TRACER_H

#include <color.h>
#include <ray.h>

class World;

class Tracer {
protected:
    World* wPtr;
public:
    Tracer();
    Tracer(World* worldPtr);
    virtual Vec3f traceRay(const Ray &ray);
};


#endif // TRACER_H
