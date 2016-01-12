#include <objects/object.h>

Triangle::Triangle(Vec3f v0, Vec3f v1, Vec3f v2) : m_v0(v0), m_v1(v1), m_v2(v2) {
}

bool Triangle::intersect(const Ray &ray, Intersection &intersection, float tNear) {
    float u, v, t;
    Vec3f v0v1 = m_v1 - m_v0;
    Vec3f v0v2 = m_v2 - m_v0;
    Vec3f pVector = ray.direction.crossProduct(v0v2);
    float determinant = v0v1.dotProduct(v0v1);
    float inverseDeterminant = 1 / determinant;
    Vec3f tVector = ray.origin - m_v0;

    u = tVector.dotProduct(pVector) * inverseDeterminant;
    if(!(u >= 0 && u <=1))
        return false;

    Vec3f qVector = tVector.crossProduct(v0v1);
    v = ray.direction.dotProduct(qVector) * inverseDeterminant;

    if (v < 0 || u + v > 1)
        return false;

    t = v0v2.dotProduct(qVector) * inverseDeterminant;

    intersection.color = Vec3f(1, 0, 0);
    intersection.t = t;
    intersection.normal = v0v1.crossProduct(v0v2);
    intersection.object = this;
    intersection.position = ray.getPoint(t);
}
