#include "../src/pluto.h"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pluto_init_window(true);

    float ang = 0;
    int org = 2 * _pluto_canvas.cheight / 3 - 1;
    for (int x = 0; x < 65; x++)
    {
        pluto_set_pix(ang * 10, org - (int)powf(2, ang));

        pluto_write_out();
        pluto_render();
        ang += 0.1;
        usleep(45000);
    }

    pluto_deinit();
}
