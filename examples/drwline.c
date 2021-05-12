#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas();
    pluto_clear(canvas);
    pluto_draw_line(canvas, (pt_t){4, 8}, (pt_t){47, 87});
    int h = canvas->height, w = canvas->width, ch = canvas->cheight, cw = canvas->cwidth;
    pluto_free_canvas(canvas);
    printf("CH: %d CW: %d TH: %d TW: %d\n", h, w, ch, cw);
}