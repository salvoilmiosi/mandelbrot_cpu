#include "image.h"

#include <cstring>

color average_color(color *colors, int num_colors) {
    if (num_colors <= 0) {
        return color();
    }
    int red = 0;
    int green = 0;
    int blue = 0;
    for (color *c = colors; c-colors < num_colors; ++c) {
        red += c->red();
        green += c->green();
        blue += c->blue();
    }
    return color(red / num_colors, green / num_colors, blue / num_colors);
}

color interpolate(color a, color b, double value) {
    //(b - a) * value + a
    int red = (b.red() - a.red()) * value + a.red();
    int green = (b.green() - a.green()) * value + a.green();
    int blue = (b.blue() - a.blue()) * value + a.blue();
    return color(red, green, blue);
}

void create_image(image *img, int width, int height) {
    memset(img, 0, sizeof(image));
    img->width = width;
    img->height = height;
    img->pixels = new color[width * height];
}

void free_image(image *img) {
    if (img->pixels != NULL) {
        delete[] img->pixels;
    }
}
