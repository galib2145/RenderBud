#ifndef OBJECT_SET_H
#define OBJECT_SET_H

#include <ray.h>
#include <objects/object.h>
#include <list>
#include <limits>

class ObjectSet : public Object {
public:
    std::list<Object*> objects;

    void addObject(Object* object) {
        objects.push_back(object);
    }

    virtual bool intersect(const Ray &ray, Intersection &finalIntersection, float tNear = std::numeric_limits<float>::max()) {
        bool intersected = false;

        for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            Object* object = *it;
            Intersection intersection;

            if(object->intersect(ray, intersection)) {
                if(intersection.t < tNear) {
                    finalIntersection = intersection;
                    intersected = true;
                }
            }
        }

        /*if(intersected) {
            finalIntersection.object->printType();
            if(ray.rayType == kPrimaryRay) {
                std::cout << "Value of t for primary ray intersection : " << finalIntersection.t << std::endl;
            }
            else {
                std::cout << "Value of t for shadow ray intersection : " << finalIntersection.t << std::endl;
                std::cout << "\n";
            }
        }*/

        return intersected;
    }
};

#endif // OBJECT_SET_H
