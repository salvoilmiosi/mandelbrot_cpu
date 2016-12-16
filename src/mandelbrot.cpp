#include "mandelbrot.h"

#include <math.h>

static int iterations = 20;

static double base = 0.99;

void set_iterations(int it) {
    iterations = it;
}

int escape_time(const complex_num &n) {
    complex_num z = n;
    int i = 0;
    for (;i < iterations; ++i) {
        if (z.mod_squared() > 4) {
            break;
        }
        z = z.squared() + n;
    }
    return i;
}

bool in_mandelbrot_set(const complex_num &n) {
    return escape_time(n) >= iterations;
}

color mandelbrot_color(double value) {
    const double positions[] = {
        0.0,
        0.16,
        0.42,
        0.6425,
        0.8575,
    };
    const color gradients[] = {
        {0, 7, 100},
        {32, 107, 203},
        {237, 255, 255},
        {255, 170, 0},
        {0,   2,   0},
    };
    const int num_grads = sizeof(positions) / sizeof(double);

    double value_d = value * num_grads;
    int value_i = value_d;

    if (value_i >= num_grads - 1) {
        return gradients[num_grads - 1];
    } else {
        return interpolate(gradients[value_i], gradients[value_i+1], value_d - value_i);
    }
}

void mandelbrot_image(image *img, complex_num center, double scale) {
    double l, t, r, b;

    if (img->width > img->height) {
        t = center.imaginary + scale;
        b = center.imaginary - scale;
        double rat = (double)img->width / img->height;
        l = center.real - scale * rat;
        r = center.real + scale * rat;
    } else {
        l = center.real - scale;
        r = center.real + scale;
        double rat = (double)img->height / img->width;
        t = center.imaginary + scale * rat;
        b = center.imaginary - scale * rat;
    }

    int width = img->width;
    int height = img->height;

    int x, y;
    color *pixel = img->pixels;

    double step_real = (r - l) / width;
    double step_imaginary = (t - b) / height;

    for (y=0; y<height; ++y) {
        for (x=0; x<width; ++x) {
            complex_num num(l + x * step_real, t - y * step_imaginary);
            int time = escape_time(num);
            if (time >= iterations) {
                *pixel = BLACK;
            } else {
                *pixel = mandelbrot_color(1 - pow(base, time));
            }
            ++pixel;
        }
    }
}
