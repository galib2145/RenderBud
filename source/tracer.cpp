#include <tracer.h>
#include <world.h>
#include <ray.h>

Tracer::Tracer(World* worldPtr) : wPtr(worldPtr) {
}

Vec3f Tracer::trace(const Ray &ray, int depth, Rng &rng) {
    Intersection intersection;
    Vec3f pixelColor, reflectionColor, refractionColor;
    float kr = 1;
    int lightU = 4;
    int lightV = 4;

    if(wPtr->objectSet.intersect(ray, intersection)) {
        pixelColor = intersection.emitted;

        if(intersection.object->m_refractiveIndex <= 0) {
            for (std::list<Light*>::iterator it = wPtr->lights.begin(); it != wPtr->lights.end(); ++it) {
                Light* light = *it;
                Vec3f lightContribution = Vec3f(0);

                for(int i = 0; i < lightU; i++) {
                    for(int j = 0; j < lightV; j++) {
                        Vec3f lightPosition, lightNormal;

                        // If floating point calculation is
                        // mistaken below(meaning int) you will
                        // get weird shadows. Might be subject
                        // to interesting investigation

                        float u1 = (i + rng.nextFloat()) / float(lightU);
                        float u2 = (j + rng.nextFloat()) / float(lightV);

                        light->sampleSurface(u1, u2, intersection.position, lightPosition, lightNormal);

                        Vec3f lightDirection = lightPosition - intersection.position;
                        float tLight = lightDirection.length();
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
                            lightContribution = lightContribution + intersection.color * facingRatio * lightEnergy;
                        }
                    }
                }

                lightContribution /= lightU * lightV;
                pixelColor = pixelColor + lightContribution;

            }
        }

        if(depth < 5) {
            if(intersection.object->m_reflectance > 0) {
                Vec3f reflectionDirection = reflect(ray.direction, intersection.normal);
                reflectionDirection.normalize();
                Vec3f reflectedRayOrigin = intersection.position + intersection.normal * 0.001f;
                Ray reflectedRay(reflectedRayOrigin, reflectionDirection);
                reflectionColor = trace(reflectedRay, depth + 1, rng) * intersection.object->m_reflectance * intersection.color;
            }

            if(intersection.object->m_refractiveIndex > 0) {
                intersection.normal.normalize();
                Vec3f refractionDirection;
                if(refract(ray.direction, intersection.normal, intersection.object->m_refractiveIndex, refractionDirection)) {
                    Vec3f refractedRayOrigin = intersection.position + refractionDirection * 0.001f;
                    Ray refractedRay(refractedRayOrigin, refractionDirection);
                    refractionColor = trace(refractedRay, depth + 1, rng);
                    fresnel(ray.direction, intersection.normal, intersection.object->m_refractiveIndex, kr);
                }
            }

            pixelColor = pixelColor + kr * reflectionColor + (1 - kr) * refractionColor;
        }

        return pixelColor;
    }

    return pixelColor;
}

