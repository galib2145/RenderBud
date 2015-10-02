#ifndef WORLD_H
#define WORLD_H

#include <display.h>
#include <camera.h>
#include <tracer.h>
#include <objectSet.h>
#include <objects/light.h>
#include <list>

class World {
public:

    Display display;
    Camera camera;
    Tracer* tracer;
    ObjectSet objectSet;
    std::list<Light*> lights;

    World();

    void build();
    void render(Display &display, Camera &camera);

    void initializeDisplay(Display &display);
    void initializeCamera(Camera &camera);

    void addObject(Object *object);
};

#endif // WORLD_H
