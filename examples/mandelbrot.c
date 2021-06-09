#include "../src/pluto.h"
#include <stdio.h>

const int maxi = 100; // Number of iter

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
                ;
            else
                pluto_set_pix(col, row);
        }
    }
}

int main()
{
    pluto_init_window(true, 31);

    create_mandelbrot();
    pluto_write_out();
    pluto_write_frame();

    pluto_deinit();
}
