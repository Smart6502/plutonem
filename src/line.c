#include "pluto.h"
#include <stdlib.h>

void pluto_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
float pluto_abs(float i) { return (i < 0) ? -i : i; }
void pluto_draw_aa_line(pt_t p0, pt_t p1)
{
    int steep = pluto_abs(p1.y - p0.y) > pluto_abs(p1.x - p0.x);

    if (steep)
    {
        pluto_swap(&p0.x, &p0.y);
        pluto_swap(&p1.x, &p1.y);
    }
    if (p0.x > p1.x)
    {
        pluto_swap(&p0.x, &p1.x);
        pluto_swap(&p0.y, &p1.y);
    }

    float dx = p1.x - p0.x, dy = p1.y - p0.y;
    float gradient = dy / dx;
    if (dx == 0.0)
        gradient = 1;

    int xpxl0 = p0.x;
    int xpxl1 = p1.x;
    float intersect_y = p0.y;

    if (steep)
    {
        int x;
        for (x = xpxl0; x <= xpxl1; x++)
        {
            pluto_set_pix((int)intersect_y, x);
            pluto_set_pix((int)intersect_y - 1, x);
            intersect_y += gradient;
        }
    }
    else
    {
        int x;
        for (x = xpxl0; x <= xpxl1; x++)
        {
            pluto_set_pix(x, (int)intersect_y);
            pluto_set_pix(x, (int)intersect_y - 1);
            intersect_y += gradient;
        }
    }
}

void pluto_draw_line(pt_t p0, pt_t p1)
{
    if (_pluto_canvas.antialias)
    {
	pluto_draw_aa_line(p0, p1);
	return;
    }

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
