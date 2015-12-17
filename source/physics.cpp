#include <physics.h>

Vec3f reflect(const Vec3f &incidentDirection, const Vec3f &normal)
{
    return incidentDirection - 2 * incidentDirection.dotProduct(normal) * normal;
}

/* How to use */

/* Pass all directions normalizing.
 * Otherwise it shall not behave
 * correctly.
 */

Vec3f refract(const Vec3f &incidentDirection, const Vec3f &normal, float refracitveIndex) {
    float cosI = incidentDirection.dotProduct(normal);
    float eta, etaT = refracitveIndex, etaI = 1.0;
    Vec3f refractionNormal = normal;

    if(cosI < 0) {
        cosI *= -1;
        refractionNormal *= -1;
    } else {
        std::swap(etaT, etaI);
    }

    eta = etaI / etaT;

    double k = 1 - eta * eta * (1 - cosI * cosI);
    if(k < 0) {
        return 0;
    } else {
        return (eta * incidentDirection + (eta * cosI - sqrtf(k)) * refractionNormal).normalize();
    }
}
