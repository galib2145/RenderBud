#include <tracer.h>
#include <world.h>
#include <ray.h>

Tracer::Tracer(World* worldPtr) : wPtr(worldPtr) {
}

Vec3f Tracer::trace(const Ray &ray, int depth) {
    Intersection intersection;
    Vec3f pixelColor;

    if(wPtr->objectSet.intersect(ray, intersection)) {
        pixelColor = intersection.emitted;

        for (std::list<Light*>::iterator it = wPtr->lights.begin(); it != wPtr->lights.end(); ++it) {
            Light* light = *it;
            Vec3f currentColor;

            float tLight;
            Vec3f lightDirection = light->getDirection(intersection, tLight);
            lightDirection.normalize();

            Vec3f shadowRayOrigin = intersection.position +  intersection.normal * 0.001f;
            Vec3f shadowRayDirection = lightDirection;
            Ray shadowRay(shadowRayOrigin, shadowRayDirection, kShadowRay);
            Intersection shadowRayIntersection;

            bool shadowRayIntersected = wPtr->objectSet.intersect(shadowRay, shadowRayIntersection, tLight);

            if(!shadowRayIntersected || shadowRayIntersection.object == light)
            {
                float facingRatio = std::max(0.0f, intersection.normal.dotProduct(lightDirection));
                Vec3f lightEnergy = light->getLightEnergy(intersection);

                currentColor = intersection.color * facingRatio * lightEnergy;
                pixelColor = pixelColor + currentColor;
            }

        }

        if(intersection.object->reflectance > 0 && depth < 5) {
            Vec3f reflectionDirection = reflect(ray.direction, intersection.normal);
            reflectionDirection.normalize();
            Vec3f reflectedRayOrigin = intersection.position + intersection.normal * 0.001f;
            Ray reflectedRay(reflectedRayOrigin, reflectionDirection);
            pixelColor = pixelColor +  (intersection.color * trace(reflectedRay, depth + 1) * intersection.object->reflectance);
            return pixelColor;
        }
    }

    return pixelColor;
}

