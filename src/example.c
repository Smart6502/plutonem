#include "lib/pluto.h"
#include <stdio.h>

struct pluto_struct_t test;

void draw_tri(int x0, int y0, int x1, int y1, int x2, int y2)
{
    pluto_draw_line(&test, x0, y0, x1, y1);
    pluto_draw_line(&test, x1, y1, x2, y2);
    pluto_draw_line(&test, x0, y0, x2, y2);   
}

int main()
{
    if (pluto_init_mode(&test))
    {
        printf("pluto lib init failed\n");
        return 1;
    }
    pluto_clear(&test);
    for (int i = 32; i < 64; i++)
    {
        for (int j = 164; j < 228; j++)
        {
            pluto_write_pix(&test, j, i);
        }
    }                                       // Rectangle
    draw_tri(25, 25, 100, 100, 25, 100);    // Triangle

    pluto_close_mode(&test);
    return 0; 
}