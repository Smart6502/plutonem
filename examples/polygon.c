#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas();
    pluto_clear(canvas);
    polygon_t *hexagon = pluto_new_polygon(6, 45, 0.39);    // Create a polygon: 6 sides / 45 pixels radius / 0.39 ort
    pluto_draw_polygon(canvas, hexagon, (pt_t){55, 55});    // Draw it
    pluto_free_polygon(hexagon);                            // Free it
    pluto_free_canvas(canvas);
}