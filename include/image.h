struct color {
    unsigned int value;

    color() {
        value = 0;
    }

    color(int rgb) {
        value = rgb;
    }

    color(int r, int g, int b, int a = 0xff) {
        value = ((r & 0xff) << 24) | ((g & 0xff) << 16) | ((b & 0xff) << 8) | a;
    }

    int red() const {
        return (value & 0xff000000) >> 24;
    }

    int green() const {
        return (value & 0x00ff0000) >> 16;
    }

    int blue() const {
        return (value & 0x0000ff00) >> 8;
    }

    int alpha() const {
        return (value & 0x000000ff);
    }
};

const color BLACK   = 0x000000ff;
const color WHITE   = 0xffffffff;
const color RED     = 0xff0000ff;
const color GREEN   = 0x00ff00ff;
const color BLUE    = 0x0000ffff;
const color YELLOW  = 0xffff00ff;
const color MAGENTA = 0xff00ffff;
const color CYAN    = 0x00ffffff;

color interpolate(color a, color b, double value);

color average_color(color *colors, int num_colors);

struct image {
    int width;
    int height;

    color *pixels;
};

void create_image(image *img, int width, int height);

void free_image(image *img);
