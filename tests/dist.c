#include "../src/inc/pluto.h"
#include <stdio.h>

#define ST_RIGHT_BASE 45
#define END_RIGHT_BASE (ST_RIGHT_BASE * 3)
#define DIV (ST_RIGHT_BASE - 20)
#define XS 10
#define XE 80

int main()
{
    pluto_canvas_t *canvas = pluto__init_canvas(0);
    pluto__clear(canvas);

    for (int i = END_RIGHT_BASE; i > ST_RIGHT_BASE; i -= i / DIV)
        pluto__draw_line(canvas, (pt_t){XS, i / 2}, (pt_t){XE, i});

    int h = canvas->height, w = canvas->width, ch = canvas->cheight, cw = canvas->cwidth;
    pluto__free_canvas(canvas);
    printf("CH: %d CW: %d TH: %d TW: %d\n", h, w, ch, cw);
}