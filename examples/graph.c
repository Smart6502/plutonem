#include "../src/pluto.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pluto_init_window(false);

    for (int x = 1; x < _pluto_canvas.cwidth; x++)
    {
        for (int y = 1; y < _pluto_canvas.cheight; y++)
        {
            pluto_set_cpix((x >> y), _pluto_canvas.cheight - 1 - (y >> x), 94, 129, 172);
        }

        pluto_write_out();
        pluto_render();
        usleep(45000);
    }

    pluto_deinit();
}
