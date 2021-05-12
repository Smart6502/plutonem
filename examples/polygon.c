#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas();
    pluto_clear(canvas);
    polygon_t *polygon = pluto_new_polygon(6, 35, 0.77);
    pluto_draw_polygon(canvas, polygon, (pt_t){40, 40});
    pluto_free_canvas(canvas);
}