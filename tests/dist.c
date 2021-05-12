#include "../src/inc/pluto.h"
#include <stdio.h>

int main()
{
    pluto_canvas_t *canvas = pluto_init_canvas();
    pluto_clear(canvas);
    
    for (int i = 150; i > 45; i -= i / 25)
    	pluto_draw_line(canvas, (pt_t){10, i / 2}, (pt_t){80, i});
    
    int h = canvas->height, w = canvas->width, ch = canvas->cheight, cw = canvas->cwidth;
    pluto_free_canvas(canvas);
    printf("CH: %d CW: %d TH: %d TW: %d\n", h, w, ch, cw);
}
