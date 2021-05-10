#include "../src/inc/pluto.h"
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
    pluto_init_mode(&test);
    if (test.height < 31 || test.width < 119) 
    {
        printf("\nThis example will not work as the terminal size is too small (min. needed 31 rows and 119 columns)");
        pluto_close_mode(&test);
        return 1;
    }
    pluto_clear(&test);
    for (int i = 32; i < 64; i++)
    {
        for (int j = 164; j < 228; j++)
        {
            pluto_write_pix(&test, j, i);
        }
    }                                         // Rectangle
    pluto_draw_line(&test, 80, 25, 150, 100); // Drawing a line between any 2 points in the terminal accurately
    draw_tri(25, 25, 100, 100, 25, 120);      // Triangle

    // I recommend fflush(stdout) after drawing a shape to avoid weird stuff happening

    pluto_close_mode(&test);
    return 0; 
}