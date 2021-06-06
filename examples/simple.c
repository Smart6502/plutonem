#include "../src/inc/pluto.h"

int main()
{
    pluto_canvas_t *canvas = pluto__init_canvas(0);
    
    pluto__clear(canvas);
    pluto__draw_line(canvas, (pt_t){5, 10}, (pt_t){20, 25});

    pluto__free_canvas(canvas);
}
