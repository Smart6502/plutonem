#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto__init_canvas(0);
    pluto__clear(canvas);
    pluto__draw_ellipse(canvas, (pt_t){60, 60}, 60 / 2, 60 / 3);
    pluto__draw_circle(canvas, (pt_t){60, 60}, 50);
    pluto__draw_circle(canvas, (pt_t){95, 70}, 20);
    pluto__free_canvas(canvas);
}
