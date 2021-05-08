#include "lib/pluto.h"
#include <stdio.h>

struct pluto_struct_t test;

static int abs(int i)
{
    return (i < 0) ? -i : i;
}

void draw_line(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        pluto_write_pix(&test, x0, y0);

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
}


void draw_tri(int x0, int y0, int x1, int y1, int x2, int y2)
{
    draw_line(x0, y0, x1, y1);
    draw_line(x1, y1, x2, y2);
    draw_line(x0, y0, x2, y2);   
}

int main()
{
    if (pluto_init_mode(&test))
    {
        printf("pluto lib init failed\n");
        return 1;
    }
    pluto_clear(&test);
    /*for (int i = 32; i < 64; i++)
    {
        for (int j = 64; j < 128; j++)
        {
            pluto_write_pix(&test, j, i);
        }
    }*/ // rectangle
    draw_tri(25, 25, 100, 100, 25, 100); // triangle

    pluto_close_mode(&test);
    return 0; 
}