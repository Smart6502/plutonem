#include "../src/pluto.h"

int main()
{
    pluto_init_window(true);

    for (int i = 0; i < 6; i++)
    {
        pluto_rast_tri((pt_t){i << i, i >> i}, (pt_t){i << i, i << i}, (pt_t){i >> i, i << i}, (pluto_colour_t){94, 129, 172});
    }

    pluto_write_out();
    pluto_render();
    pluto_deinit();
}
