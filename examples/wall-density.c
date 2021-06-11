#include "../src/pluto.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const float density = 0.6; // Pixel density (low => high density, high => low density)
const int count = 4;       // Number of objects

int main()
{
    pluto_init_window(true, 31);

    float x, y;
    for (x = 1; x < _pluto_canvas.cwidth / count; x += density)
    {
        for (y = 1; y < _pluto_canvas.cheight; y += density)
        {
            int r = (int)(x / y);
            pluto_set_pix(r * x, r * y);
        }

        pluto_write_out();
        pluto_write_frame();
        fflush(stdout);
        usleep(45000);
    }

    pluto_deinit();
}
