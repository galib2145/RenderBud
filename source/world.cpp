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

    Object* pointLight1 = new PointLight(Vec3f(1,1,1), 2.0f, Vec3f(0, 15, 1));
    Object* pointLight2 = new PointLight(Vec3f(1,1,.5), 0.75f, Vec3f(20, 30, 5));

    Object* areaLight1 = new AreaLight(Vec3f(1, 1, 1), 1.0f, Vec3f(5, 0, 0), Vec3f(0, 0, 5), Vec3f(-2, 8, 0));
    Object* areaLight2 = new AreaLight(Vec3f(1, 1, .5), 0.75f, Vec3f(4, 0, 0), Vec3f(0, 0, 4), Vec3f(-2, 6, 0));

    Object* sphere1 = new Sphere(Vec3f(4, 2, -2), 2.0f, Vec3f(.7, .7, 1), 1, 0);
    Object* sphere2 = new Sphere(Vec3f(-4, 1, 6), 3.0f, Vec3f(.7, .7, .7), 1, .2);
    Object* sphere = new Sphere(Vec3f(2, 2, 4), 2.0f, Vec3f(.7, .7, .7), 1, 0.96, .96);

    Object* triangle = new Triangle(Vec3f(-2, 2, 0), Vec3f(1, 4, 0), Vec3f(2, 2, 0));

    Object* horizontalPlane = new Plane(Vec3f(0, -2, 0), Vec3f(0, 1, 0), Vec3f(.7, .7, .7), 0);
    Object* backPlane = new Plane(Vec3f(0, 0, -6), Vec3f(0, 0, 1), Vec3f(.5, .3, .5), 0);

    addObject(horizontalPlane);
    addObject(backPlane);
    addObject(sphere1);
    addObject(sphere2);
    addObject(sphere);

    //addObject(triangle);

    addObject(pointLight1);
    //addObject(pointLight2);

    addObject(areaLight1);
    addObject(areaLight2);
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

                float x = (i + rng.nextFloat()) / (float)display.width;
                float y = 1 - ((j + rng.nextFloat()) / (float)display.height);

                Ray ray = camera.makeRay(x, y);
                pixelColor = pixelColor + tracer->trace(ray, 1, rng);
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
