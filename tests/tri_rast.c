#include "../src/inc/pluto.h"

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas();
    pluto_clear(canvas);

    pluto_rast_tri(canvas, (pt_t){20, 10}, (pt_t){30, 55}, (pt_t){70, 40});

    pluto_free_canvas(canvas);
}
