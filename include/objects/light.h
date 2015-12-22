#ifndef LIGHT_H
#define LIGHT_H

#include <geometry.h>
#include <cmath>

class Light : public Object {
public:
    Vec3f color;
    float intensity;
    Light(Vec3f color, float intensity) {
        this->color = color;
        this->intensity = intensity;
    }

    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max()) {
        return false;
    }

    Vec3f emitted() {
        return color * intensity;
    }

    virtual Vec3f getDirection(Intersection &intersection, float &distance) = 0;
    virtual Vec3f getLightEnergy(Intersection &intersection) = 0;
};

class PointLight : public Light {

public:
    Vec3f position;
    PointLight(Vec3f color, float intensity, Vec3f position) : Light(color, intensity) {
        this->position = position;
    }

    virtual bool intersect(const Ray &ray, Intersection &intersection, float tNear = std::numeric_limits<float>::max() ) {
        return false;
    }

    virtual Vec3f getDirection(Intersection &intersection, float &distance) {
        Vec3f direction = position - intersection.position;
        distance = sqrtf(direction.norm());
        direction /= distance;
        return direction;
    }

    virtual Vec3f getLightEnergy(Intersection &intersection) {
        float r2 = (position - intersection.position).norm();
        Vec3f totalEnergy = color * intensity;
        totalEnergy /= M_PI;
        return totalEnergy;
    }
};

class AreaLight : public Light {
public:
    Vec3f m_side1, m_side2, m_position, side1Normalized, side2Normalized;
    float side1Length, side2Length;
    AreaLight(Vec3f color,
              float intensity,
              Vec3f side1,
              Vec3f side2,
              Vec3f position)
            : Light(color, intensity), m_side1(side1), m_side2(side2), m_position(position) {

            side1Length = m_side1.length();
            side2Length = m_side2.length();

            side1Normalized = m_side1.getNormalizedVector();
            side2Normalized = m_side2.getNormalizedVector();
    }

    virtual bool intersect(const Ray &ray,
                           Intersection &intersection,
                           float tNear = std::numeric_limits<float>::max()) {
            Vec3f planeNormal = m_side1.crossProduct(m_side2).normalize();
            float d = ray.direction.dotProduct(planeNormal);
            if(d == 0) {
                return false;
            }

            float n = (m_position - ray.origin).dotProduct(planeNormal);
            float t = n / d;

            if(t < 0) {
                return false;
            }

            Vec3f intersectionPosition = ray.getPoint(t);
            Vec3f relativeIntersectionPosition = intersectionPosition - m_position;

            float localIntersectionPositionX = relativeIntersectionPosition.dotProduct(side1Normalized);
            float localIntersectionPositionY = relativeIntersectionPosition.dotProduct(side2Normalized);

            Vec3f localIntersectionPosition(localIntersectionPositionX, localIntersectionPositionY, 0);

            if(localIntersectionPosition.x < 0 || localIntersectionPosition.x > side1Length ||
               localIntersectionPosition.y < 0 || localIntersectionPosition.y > side2Length) {
                return false;
            }

            intersection.emitted = color * intensity;
            intersection.t = t;
            intersection.position = intersectionPosition;
            intersection.object = this;
            intersection.normal = planeNormal;

            if(d < 0) {
                intersection.normal *= -1;
            }

            return true;
    }

    virtual Vec3f getDirection(Intersection &intersection, float &distance) {
        Vec3f direction = (m_position - intersection.position);
        distance = direction.length();
        return direction;
    }

    virtual Vec3f getLightEnergy(Intersection &intersection) {
        return color * intensity;
    }

    virtual bool sampleSurface(float u1,
                               float u2,
                               const Vec3f& referencePosition,
                               Vec3f& surfacePosition,
                               Vec3f& surfaceNormal) {
        surfaceNormal = m_side1.crossProduct(m_side2).normalize();
        surfacePosition = m_position + m_side1 * u1 + m_side2 * u2;

        if (surfaceNormal.dotProduct(surfacePosition - referencePosition) > 0.0f)
            surfaceNormal *= -1.0f;

        return true;
    }

};


#endif // LIGHT_H
