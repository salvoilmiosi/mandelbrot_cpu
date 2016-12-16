#include <SDL2/SDL.h>

#include "mandelbrot.h"

#include <cstdio>
#include <algorithm>

static int window_width = 900;
static int window_height = 600;

static const int multisample = 4;
static int save_width = 1920;
static int save_height = 1080;

static complex_num center{-0.5, 0.0};
static double scale = 1.0;
static double iterations = 200;

static SDL_Surface *last_surface = NULL;

void update_mandelbrot(SDL_Window *win) {
    if (last_surface != NULL) {
        SDL_FreeSurface(last_surface);
    }
    image img;
    create_image(&img, window_width, window_height);
    mandelbrot_image(&img, center, scale);
    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(img.pixels, img.width, img.height, 32, sizeof(color) * img.width, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_Surface *winsurf = SDL_GetWindowSurface(win);
    SDL_BlitSurface(surf, &surf->clip_rect, winsurf, &winsurf->clip_rect);
    SDL_UpdateWindowSurface(win);
    last_surface = surf;
    free_image(&img);
}

void calculate_center_and_scale(int start_x, int start_y, int end_x, int end_y) {
    int min_len = window_width < window_height ? window_width : window_height;
    double scale_len = 2 * scale / min_len;
    int dx_to_center = start_x - (window_width / 2);
    int dy_to_center = start_y - (window_height / 2);
    center.real += (double) dx_to_center * scale_len;
    center.imaginary -= (double) dy_to_center * scale_len;
    int dx_to_start = start_x < end_x ? end_x - start_x : start_x - end_x;
    int dy_to_start = start_y < end_y ? end_y - start_y : start_y - end_y;
    scale = dx_to_start > dy_to_start ? (double) dx_to_start * scale_len : (double) dy_to_start * scale_len;
}

void save_image() {
    image img;

    create_image(&img, save_width * multisample, save_height * multisample);
    mandelbrot_image(&img, center, scale);

    SDL_Surface *surf;

    if (multisample > 1) {
        surf = SDL_CreateRGBSurface(0, save_width, save_height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
        SDL_LockSurface(surf);
        for (int y=0; y<surf->h; ++y) {
            for (int x=0; x<surf->w; ++x) {
                color colors[multisample * multisample];
                for (int i=0; i<multisample*multisample; ++i) {
                    int xx = i % multisample;
                    int yy = i / multisample;
                    colors[i] = img.pixels[(y * multisample + yy) * img.width + (x * multisample + xx)];
                }
                *((int *)(surf->pixels) + y * surf->w + x) = average_color(colors, multisample * multisample).value;
            }
        }
        SDL_UnlockSurface(surf);
    } else {
        surf = SDL_CreateRGBSurfaceFrom(img.pixels, img.width, img.height, 32, sizeof(color) * img.width, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    }
    if (surf != NULL) {
        SDL_SaveBMP(surf, "mandelbrot.bmp");
        SDL_FreeSurface(surf);
    } else {
        fprintf(stderr, "%s", SDL_GetError());
    }
    free_image(&img);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not init SDL\n");
        return 1;
    }

    image img;
    create_image(&img, window_width, window_height);
    mandelbrot_image(&img, center, scale);

    SDL_Window *win = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);

    set_iterations(iterations);
    update_mandelbrot(win);

    SDL_Event e;

    bool quit = false;

    int start_x, start_y, end_x, end_y;

    while(!quit && SDL_WaitEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            start_x = e.button.x;
            start_y = e.button.y;
            break;
        case SDL_MOUSEBUTTONUP:
            calculate_center_and_scale(start_x, start_y, end_x, end_y);
            update_mandelbrot(win);
            break;
        case SDL_MOUSEMOTION:
            end_x = e.button.x;
            end_y = e.button.y;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_PLUS:
                ++iterations;
                set_iterations(iterations);
                update_mandelbrot(win);
                break;
            case SDLK_MINUS:
                --iterations;
                set_iterations(iterations);
                update_mandelbrot(win);
                break;
            case SDLK_r:
                center = complex_num(-0.5, 0.0);
                scale = 1.0;
                update_mandelbrot(win);
                break;
            case SDLK_s:
                save_image();
                break;
            }
            break;
        default:
            break;
        }
    }

    if (last_surface != NULL) {
        SDL_FreeSurface(last_surface);
    }
    SDL_Quit();
    return 0;
}
