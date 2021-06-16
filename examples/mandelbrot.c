#include "../src/pluto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxi = 100; // Number of iter

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
            if (iter >= maxi) {
                pluto_set_cpix(col, row, (int)(x * c_re * 2048), (int)(y * c_im * 4096), iter + maxi * x * col * row);
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
