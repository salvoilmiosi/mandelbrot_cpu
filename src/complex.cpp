#include "complex.h"

#include <math.h>

complex_num complex_num::polar(double t, double m) {
    complex_num ret;
    ret.real = cos(t) * m;
    ret.imaginary = sin(t) * m;
    return ret;
}

complex_num complex_num::squared() const {
    return complex_num(real * real - imaginary * imaginary, 2 * real * imaginary);
}

double complex_num::mod() const {
    return sqrt(real * real + imaginary * imaginary);
}

double complex_num::mod_squared() const {
    return real * real + imaginary * imaginary;
}

double complex_num::theta() const {
    return atan2(imaginary, real);
}
