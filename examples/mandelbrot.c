#include "../src/pluto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxi = 50; // Number of iter

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

pluto_colour_t HsvToRgb(HsvColor hsv)
{
    pluto_colour_t rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

void create_mandelbrot()
{
    for (int row = 0; row < _pluto_canvas.cheight; row++)
    {
        for (int col = 0; col < _pluto_canvas.cwidth; col++)
        {
            double c_re = (col - _pluto_canvas.cwidth / 2) * 4.0 / _pluto_canvas.cwidth;
            double c_im = (row - _pluto_canvas.cheight / 2) * 4.0 / _pluto_canvas.cwidth;
            double x = 0, y = 0;
            int iter = 0;

            while (x * x + y * y < 4 && iter < maxi)
            {
                double x_new = x * x - y * y + c_re;
                y = 2 * x * y + c_im;
                x = x_new;
                iter++;
            }

            if (iter < maxi)
            {
                pluto_colour_t tmp = HsvToRgb((HsvColor){ (int)(255 * iter / maxi), (int)(255 * iter / maxi), (int)(255 * iter / maxi)} );
                pluto_set_cpix(col, row, tmp.r, tmp.g, tmp.b);
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc > 2)
        return 1;
    if (argc == 2)
    {
        maxi = atoi(argv[1]);
    }

    srand(clock());

    pluto_init_window(true);

    create_mandelbrot();
    pluto_write_out();
    pluto_render();

    pluto_deinit();
}
