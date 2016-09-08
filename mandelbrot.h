#include "math/complex.h"
#include "image.h"

void set_iterations(int it);

int escape_time(const complex_num &n);

bool in_mandelbrot_set(const complex_num &n);

void mandelbrot_image(image *img, complex_num center, double scale);
