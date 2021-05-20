#include "../src/inc/pluto.h"

int main()
{
    pluto_canvas_t *canvas = pluto__init_canvas(0);
    pluto__clear(canvas);

    pluto__rast_tri(canvas, (pt_t){35, 20}, (pt_t){55, 55}, (pt_t){15, 75});

    pluto__free_canvas(canvas);
}