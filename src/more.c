#include "inc/pluto.h"
#include <stdio.h>

#ifdef PLUTO_EXTRAS
static int pluto_abs(int i) { return (i < 0) ? -i : i; }
void pluto_draw_line(struct pluto_struct_t *__info, int x0, int y0, int x1, int y1)
{
    #ifdef ERROR_CHECK
    if (x0 < 0 || y0 < 0 || __info->width * 2 < x1 || __info->height * 4 < y1) return;
    #endif
    int dx = pluto_abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = pluto_abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        pluto_write_pix(__info, x0, y0);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
    fflush(stdout);
}

#endif
