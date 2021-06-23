#include "../src/pluto.h"
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pluto_init_window();

    for (int t = 0; t < 8; t++)
    {
        for (int i = 1; i < _pluto_canvas.cheight; i++)
        {
            for (int j = 1; j < _pluto_canvas.cwidth; j++)
            {
                if ((j | i) & t)
                    pluto_set_cpix(j % 256, i % 256, j % 256, i % 256, i * j % 256);
            }
        }

        pluto_write_out();
        pluto_render();
        usleep(350000);
    }

    pluto_deinit();
    return 0;
}
