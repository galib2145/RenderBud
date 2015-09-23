#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    int height, width;
    float aspectRatio;

    Display() {
    }

    Display(int width, int height) {
        this->height = height;
        this->width = width;
        this->aspectRatio = width / (float)height;
    };
};

#endif // DISPLAY_H
