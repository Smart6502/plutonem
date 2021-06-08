#include "../src/pluto.h"
#include <signal.h>
#include <stdio.h>
#include <time.h>

const int wait = 45000;
const struct timespec wts = {
	.tv_sec = wait / 100000,
	.tv_nsec = (wait % 100000) * 1000
};

int main()
{
    pluto_init_window(true, 94, 129, 172);
    
    for (int x = 0; x < _pluto_canvas.cwidth; x++)
    {
	for (int y = 0; y < _pluto_canvas.cheight; y++)
	{
	    pluto_set_pix((x >> y), _pluto_canvas.cheight - 1 - (y >> x));
	}
    	
	pluto_write_out();
        pluto_write_frame();
	fflush(stdout);	
	nanosleep(&wts, NULL);
    }

    pluto_deinit();
}
