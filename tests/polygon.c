#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas(1);
    pluto_clear(canvas);
    polygon_t *hexagon = pluto_new_polygon(6, 45, 0.39);
    pluto_draw_polygon(canvas, hexagon, (pt_t){55, 55});
    pluto_free_polygon(hexagon);
    pluto_free_canvas(canvas);
}