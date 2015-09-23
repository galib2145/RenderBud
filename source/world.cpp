#include <world.h>
#include <ray.h>
#include <fstream>
#include <objects/sphere.h>

World::World() {
}

void World::initializeDisplay(Display &display) {
    this->display = display;
}

void World::initializeCamera(Camera &camera) {
    this->camera = camera;
}

void World::build() {
    this->tracer = new Tracer(this);
    Vec3f center = Vec3f(0, 0, -2);
    //Sphere sphere(center, 4.0f);
    Object* sphere = new Sphere(center, .4f);
    objectSet.addObject(sphere);
}

void World::render(Display &display, Camera &camera) {
    initializeCamera(camera);
    initializeDisplay(display);

    Vec3f *framebuffer = new Vec3f[display.width * display.height];
    Vec3f *pix = framebuffer;

    for(int j = 0; j < display.height; j++) {
        for(int i = 0; i < display.width; i++) {

            Vec3f origin;
            camera.worldToCamera.multVecMatrix(Vec3f(0), origin);

            float x = (2 * (i + 0.5) / (float)display.width - 1) * display.aspectRatio * camera.scalingFactor;
            float y = (1 - 2 * (j + 0.5) / (float)display.height) * camera.scalingFactor;

            Vec3f direction;
            camera.worldToCamera.multDirMatrix(Vec3f(x, y, -1), direction);

            /*std::cout << display.aspectRatio << std::endl;
            std::cout << i << ", " << j << std::endl;
            std::cout << x << ", " << y << std::endl;
            std::cout << "Ray : " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
            std::cout << "" << std::endl;*/

            direction.normalize();

            Ray ray(origin, direction);

            Intersection intersection;

            if(objectSet.intersect(ray, intersection)) {
                *(pix++) = intersection.color;
            } else {
                *(pix++) = Vec3f(0,0,0);
            }

            //*(pix++) = this->tracer->traceRay(ray);

        }
    }

    std::ofstream ofs("./out.ppm");
    ofs << "P6\n" << display.width << " " << display.height << "\n255\n";
    for (uint32_t i = 0; i < display.height * display.width; ++i) {
        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close();

    delete [] framebuffer;
}
