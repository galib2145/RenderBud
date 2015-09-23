#include <iostream>

#include <geometry.h>
#include <ray.h>
#include <objects/sphere.h>
#include <display.h>
#include <camera.h>
#include <world.h>

using namespace std;

int main()
{
    cout << "Rendering." << endl;
    Display display(640, 480);

    Matrix44f cameraToWorld;
    Camera camera(90, cameraToWorld);

    World world;
    world.build();
    world.render(display, camera);

    return 0;
}
