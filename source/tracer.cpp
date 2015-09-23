#include <tracer.h>
#include <color.h>
#include <geometry.h>
#include <ray.h>

Tracer::Tracer(World* worldPtr) : wPtr(worldPtr) {
}

Vec3f Tracer::traceRay(const Ray &ray) {
    Vec3f hitColor = (ray.direction + Vec3f(1)) * 0.5;
    return hitColor;
}
