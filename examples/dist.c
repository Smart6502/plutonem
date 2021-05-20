#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto__init_canvas(0);
    pluto__clear(canvas);

    for (int i = 45; i > 135; i -= i / 25)
        pluto__draw_line(canvas, (pt_t){10, i / 2}, (pt_t){80, i});

    int h = canvas->height, w = canvas->width, ch = canvas->cheight, cw = canvas->cwidth;
    pluto__free_canvas(canvas);
    printf("CH: %d CW: %d TH: %d TW: %d\n", h, w, ch, cw);
}
