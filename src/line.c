#include "pluto.h"
#include <stdlib.h>

void pluto_draw_line(pt_t p0, pt_t p1)
{
    int dx = (int)abs(p1.x - p0.x), sx = p0.x < p1.x ? 1 : -1;
    int dy = (int)abs(p1.y - p0.y), sy = p0.y < p1.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        pluto_set_pix(p0.x, p0.y);

        if (p0.x == p1.x && p0.y == p1.y)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            p0.x += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            p0.y += sy;
        }
    }
}
