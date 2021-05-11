#include "../src/inc/pluto.h"

int main()
{
	pluto_canvas_t *canvas = pluto_init_canvas();
	pluto_clear(canvas);
	pluto_draw_line(canvas, (pt_t){4, 8}, (pt_t){23, 17});
	pluto_free_canvas(canvas);	
}
