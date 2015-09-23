#ifndef OBJECT_SET_H
#define OBJECT_SET_H

#include <objects/object.h>
#include <list>
#include <limits>

class ObjectSet : public Object {
public:
    std::list<Object*> objects;

    void addObject(Object* object) {
        objects.push_back(object);
    }

    bool intersect(const Ray &ray, Intersection &finalIntersection) {
        float t = std::numeric_limits<float>::max();
        bool intersected = false;

        for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            Object* object = *it;
            Intersection intersection;

            if(object->intersect(ray, intersection)) {
                if(intersection.t < t) {
                    finalIntersection = intersection;
                    intersected = true;
                }
            }
        }

        return intersected;
    }
};

#endif // OBJECT_SET_H
