#include "../src/pluto.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

const float density = 1.3;  // Pixel density (low => high density, high => low density)

int main()
{
    pluto_init_window(true, 31);

    float x, y;
    for (x = 1; x < _pluto_canvas.cwidth / 3; x += density)
    {
        for (y = 1; y < _pluto_canvas.cheight; y += density)
        {
	    float r = x / y;
	    float m = powf(r, 1 / r);

            pluto_set_pix(m * x, _pluto_canvas.cheight - 1 - (m * y));
        }

        pluto_write_out();
        pluto_write_frame();
        fflush(stdout);
	usleep(50000);
    }

    pluto_deinit();
}