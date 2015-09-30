#include <world.h>
#include <ray.h>
#include <fstream>

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

    Object* sphere1 = new Sphere(Vec3f(0, .5, -1), .35f, Vec3f(1, 1, 1));
    Object* sphere2 = new Sphere(Vec3f(0, .2, -.5), .15f, Vec3f(1, 1, 1));
    Object* plane = new Plane(Vec3f(0, -2, 0), Vec3f(0, 1, 0), Vec3f(1, 1, 1), true);

    objectSet.addObject(sphere1);
    objectSet.addObject(sphere2);
    objectSet.addObject(plane);
}

void World::render(Display &display, Camera &camera) {
    initializeCamera(camera);
    initializeDisplay(display);

    Rng rng;

    Vec3f *framebuffer = new Vec3f[display.width * display.height];
    Vec3f *pix = framebuffer;
    int noOfSamples = 32;

    for(int j = 0; j < display.height; j++) {
        for(int i = 0; i < display.width; i++) {
            Vec3f pixelColor;
            for(int k = 1; k <= noOfSamples; k++) {

                Vec3f origin;
                camera.worldToCamera.multVecMatrix(Vec3f(0), origin);

                float x = (2 * (i + rng.nextFloat()) / (float)display.width - 1) * display.aspectRatio * camera.scalingFactor;
                float y = (1 - 2 * (j + rng.nextFloat()) / (float)display.height) * camera.scalingFactor;

                Vec3f direction;
                camera.worldToCamera.multDirMatrix(Vec3f(x, y, -1), direction);

                direction.normalize();


                Ray ray(origin, direction);
                Intersection intersection;

                if(objectSet.intersect(ray, intersection)) {
                    float facingRatio = std::max(0.0f, intersection.normal.dotProduct(-ray.direction));
                    pixelColor = pixelColor + intersection.color * facingRatio;
                }
            }

            pixelColor /= noOfSamples;
            *(pix++) = pixelColor;
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
