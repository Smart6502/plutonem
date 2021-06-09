#include "../src/pluto.h"

int main()
{
    pluto_init_window(true, 31);
    pluto_rast_tri((pt_t){40, 20}, (pt_t){80, 40}, (pt_t){20, 80});
    pluto_write_out();
    pluto_write_frame();
    pluto_deinit();
}
