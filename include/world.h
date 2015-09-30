#ifndef WORLD_H
#define WORLD_H

#include <color.h>
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
    Light* light;

    World();

    void build();
    void render(Display &display, Camera &camera);

    void initializeDisplay(Display &display);
    void initializeCamera(Camera &camera);

    void drawPixel(int row, int column, Color color);
};

#endif // WORLD_H
