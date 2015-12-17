#include <physics.h>
#include <utils.h>

Vec3f reflect(const Vec3f &incidentDirection, const Vec3f &normal)
{
    return incidentDirection - 2 * incidentDirection.dotProduct(normal) * normal;
}

// [Comment]
// Pass all directions normalizing.
// Otherwise it shall not behave
// correctly.
// [Comment]

bool refract(const Vec3f &incidentDirection, const Vec3f &normal, float refractiveIndex, Vec3f &refractionDirection) {
    float cosI = incidentDirection.dotProduct(normal);
    float eta, etaT = refractiveIndex, etaI = 1.0;
    Vec3f refractionNormal = normal;

    if(cosI < 0) {
        cosI *= -1;
    } else {
        refractionNormal *= -1;
        std::swap(etaT, etaI);
    }

    eta = etaI / etaT;

    double k = 1 - eta * eta * (1 - cosI * cosI);
    if(k < 0) {
        return false;
    } else {
        refractionDirection = eta * incidentDirection + (eta * cosI - sqrtf(k)) * refractionNormal;
        return true;
    }
}

void fresnel(const Vec3f &incidentDirection, const Vec3f &normal, const float &refractiveIndex, float &kr)
{
    float cosI = clamp(-1, 1, incidentDirection.dotProduct(normal));
    float etaI = 1, etaT = refractiveIndex;
    if (cosI > 0) { std::swap(etaI, etaT); }
    float sinT = etaI / etaT * sqrtf(std::max(0.f, 1 - cosI * cosI));

    if (sinT >= 1) {
        kr = 1;
    } else {
        float cosT = sqrtf(std::max(0.f, 1 - sinT * sinT));
        cosI = fabsf(cosI);
        float Rs = ((etaT * cosI) - (etaI * cosT)) / ((etaT * cosI) + (etaI * cosT));
        float Rp = ((etaI * cosI) - (etaT * cosT)) / ((etaI * cosI) + (etaT * cosT));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
}
