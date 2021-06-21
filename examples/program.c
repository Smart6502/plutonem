#include "../src/pluto.h"
#include <stdlib.h>

int main()
{
    pluto_init_window(false);

    for (int i = 1; i < _pluto_canvas.cheight; i++)
    {
        for (int j = 1; j < _pluto_canvas.cwidth; j++)
        {
            if (i & j)
                pluto_set_cpix(j, i, i % 256, j % 256, i * j % 256);
        }
    }

    pluto_write_out();
    pluto_render();

    pluto_deinit();
    return 0;
}
