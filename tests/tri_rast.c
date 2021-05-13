#include "../src/inc/pluto.h"

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas(0);
    pluto_clear(canvas);

    pluto_rast_tri(canvas, (pt_t){35, 20}, (pt_t){55, 55}, (pt_t){15, 75});

    pluto_free_canvas(canvas);
}