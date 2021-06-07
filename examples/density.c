#include "../src/pluto.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int wait = 35000;
const struct timespec wts = {
	.tv_sec = wait / 100000,
	.tv_nsec = (wait % 100000) * 1000
};

int main()
{
    pluto_init_window(true);

    float x, y;
    for (x = 1; x < _pluto_canvas.cwidth / 4; x += 0.5)
    {
	for (y = 1; y < _pluto_canvas.cheight / 2; y += 0.5)
	{
            int r = (int)(x / y);
	    pluto_set_pix(r * x, r * y);
	}

	pluto_write_out();
	pluto_write_frame();
	fflush(stdout);
	nanosleep(&wts, NULL);
    }
    
    pluto_deinit();
}
