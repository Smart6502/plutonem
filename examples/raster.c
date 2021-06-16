#include "../src/pluto.h"

int main()
{
    pluto_init_window(true);

    for (int i = 0; i < 8; i++)
    {
        pluto_rast_tri((pt_t){1 << i, i << 1}, (pt_t){i << 1, 1 << i}, (pt_t){1 << i, 1 << i}, (pluto_colour_t){94 + i * 2, 129 + i * 2, 172 + i * 2});
    }

    pluto_write_out();
    pluto_render();
    pluto_deinit();
}
