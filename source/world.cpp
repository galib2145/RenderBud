#include <world.h>

World::World() {
}

void World::initializeDisplay(Display &display) {
    this->display = display;
}

void World::initializeCamera(Camera &camera) {
    this->camera = camera;
}

void World::addObject(Object* object) {
    objectSet.addObject(object);
    if (dynamic_cast<Light*>(object)) {
        Light* light = dynamic_cast<Light*>(object);
        lights.push_back(light);
    }
}

void World::build() {

    this->tracer = new Tracer(this);

    Object* pointLight1 = new PointLight(Vec3f(1,1,1), 3.0f, Vec3f(0, .5, 0));
    Object* pointLight2 = new PointLight(Vec3f(1,1,1), 1.0f, Vec3f(.5, .5, 0));

    Object* sphere1 = new Sphere(Vec3f(0, .2, -.5), .15f, Vec3f(.7, .7, .7), 1, 0.7);
    Object* sphere2 = new Sphere(Vec3f(-.5, .2, -.5), .07f, Vec3f(.7, .7, .7), 1, 0.3);
    Object* sphere3 = new Sphere(Vec3f(.5, .2, -.5), .07f, Vec3f(.7, .7, .7), 1, 0.3);

    Object* horizontalPlane = new Plane(Vec3f(0, -2, 0), Vec3f(0, 1, 0), Vec3f(.4, .3, .3), true);
    Object* verticalPlane = new Plane(Vec3f(0, 0, -7), Vec3f(0, 0, 1), Vec3f(0, 0, 1), false);

    addObject(sphere1);
    addObject(horizontalPlane);
    addObject(sphere2);
    addObject(sphere3);

    addObject(pointLight1);
    addObject(pointLight2);
}

void World::render(Display &display, Camera &camera) {
    initializeCamera(camera);
    initializeDisplay(display);

    Rng rng;

    Vec3f *framebuffer = new Vec3f[display.width * display.height];
    Vec3f *pix = framebuffer;
    int noOfSamples = 8;

    for(int j = 0; j < display.height; j++) {
        for(int i = 0; i < display.width; i++) {
            Vec3f pixelColor;
            for(int k = 1; k <= noOfSamples; k++) {

                Vec3f origin;
                Intersection intersection;
                camera.worldToCamera.multVecMatrix(Vec3f(0), origin);

                float x = (2 * (i + rng.nextFloat()) / (float)display.width - 1) * display.aspectRatio * camera.scalingFactor;
                float y = (1 - 2 * (j + rng.nextFloat()) / (float)display.height) * camera.scalingFactor;

                Vec3f direction;
                camera.worldToCamera.multDirMatrix(Vec3f(x, y, -1), direction);
                direction.normalize();

                Ray ray(origin, direction);
                pixelColor = pixelColor + tracer->trace(ray, 1);
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
