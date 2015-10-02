#include <tracer.h>
#include <world.h>

Tracer::Tracer(World* worldPtr) : wPtr(worldPtr) {
}

Vec3f Tracer::trace(const Ray &ray) {
    Intersection intersection;
    Vec3f pixelColor;

    if(wPtr->objectSet.intersect(ray, intersection)) {
        pixelColor = intersection.emitted;

        for (std::list<Light*>::iterator it = wPtr->lights.begin(); it != wPtr->lights.end(); ++it) {
            Light* light = *it;
            Vec3f currentColor = light->shade(intersection);
            pixelColor = pixelColor + currentColor;
        }
    }

    return pixelColor;
}
