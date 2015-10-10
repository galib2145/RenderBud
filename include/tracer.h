#ifndef TRACER_H
#define TRACER_H

#include <ray.h>
#include <geometry.h>
#include <intersection.h>


class World;

class Tracer {
protected:
    World* wPtr;
public:
    Tracer();
    Tracer(World* worldPtr);
    virtual Vec3f trace(const Ray &ray, int depth);
};


#endif // TRACER_H
