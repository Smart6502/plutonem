#include "../src/pluto.h"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

const int wait = 45000;
const struct timespec wts = {
    .tv_sec = wait / 100000,
    .tv_nsec = (wait % 100000) * 1000};

int main()
{
    pluto_init_window(true, 35);

    float ang = 0;
    int org = 2 * _pluto_canvas.cheight / 3 - 1;
    for (int x = 0; x < 65; x++)
    {
        pluto_set_pix(ang * 10, org - (int)powf(2, ang));

        pluto_write_out();
        pluto_write_frame();
        fflush(stdout);
        ang += 0.1;
        nanosleep(&wts, NULL);
    }

    pluto_deinit();
}
