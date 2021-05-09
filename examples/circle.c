#include "../src/lib/pluto.h"

struct pluto_struct_t test;

void draw_circle(int xc, int yc, int x, int y)
{
    pluto_write_pix(&test, xc + x, yc + y);
    pluto_write_pix(&test, xc - x, yc + y);
    pluto_write_pix(&test, xc + x, yc - y);
    pluto_write_pix(&test, xc - x, yc - y);
    pluto_write_pix(&test, xc + y, yc + x);
    pluto_write_pix(&test, xc - y, yc + x);
    pluto_write_pix(&test, xc + y, yc - x);
    pluto_write_pix(&test, xc - y, yc - x);
}

void display_circle(int xc, int yc, int rad)
{
    int x = 0, y = rad;
    int d = 3 - 2 * rad;
    draw_circle(xc, yc, x, y);
    while (y >= x)
    {
        x++;

        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        draw_circle(xc, yc, x, y);
    }
}


int main()
{
    pluto_init_mode(&test);
    pluto_clear(&test);

    display_circle(40, 40, 30);

    pluto_close_mode(&test);
}