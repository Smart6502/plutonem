#include "../src/pluto.h"

int main()
{
    pluto_init_window(true);
    pluto_rast_tri((pt_t){40, 20}, (pt_t){80, 40}, (pt_t){20, 80});
    pluto_write_out();
    pluto_render();
    pluto_deinit();
}
