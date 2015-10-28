#include <iostream>

#include <geometry.h>
#include <display.h>
#include <camera.h>
#include <world.h>

using namespace std;

int main()
{
    cout << "Rendering." << endl;
    Display display(512, 512);

    Matrix44f cameraToWorld;
    Camera camera(45, Vec3f(0.0f, 10.0f, 20.0f),
                      Vec3f(0.0f, 0.0f, 0.0f),
                      Vec3f(0.0f, 1.0f, 0.0f));

    World world;
    world.build();
    world.render(display, camera);

    return 0;
}
