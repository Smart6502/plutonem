#include "../src/pluto.h"
#include <stdio.h>

int main()
{
    pluto_init_window(true);
    for (int x = 0; x < _pluto_canvas.cwidth; x++)
    {
	for (int y = 0; y < _pluto_canvas.cheight; y++)
	{
	    pluto_set_pix(x >> y, y >> x);
    	}
	pluto_write_out();
        pluto_write_frame(); 
	fflush(stdout);	
    }
    pluto_deinit();
}
