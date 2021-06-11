#include "../src/pluto.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pluto_init_window(true, 35);

    for (int x = 1; x < _pluto_canvas.cwidth; x++)
    {
        for (int y = 1; y < _pluto_canvas.cheight; y++)
        {
            pluto_set_pix((x >> y), _pluto_canvas.cheight - 1 - (y >> x));
        }

        pluto_write_out();
        pluto_write_frame();
        fflush(stdout);
        usleep(45000);
    }

    pluto_deinit();
}
