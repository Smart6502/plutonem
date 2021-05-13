#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas(0);
    pluto_clear(canvas);
    pluto_draw_ellipse(canvas, (pt_t){60, 60}, 60 / 2, 60 / 3);
    pluto_draw_circle(canvas, (pt_t){60, 60}, 45);
    pluto_free_canvas(canvas);
}