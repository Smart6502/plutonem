#include "../src/pluto.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const float density = 0.6; // Pixel density (low => high density, high => low density)
const int count = 4;       // Number of objects

int main()
{
    pluto_init_window();

    FILE *fp = fopen("wall", "w");

    float x, y;
    for (x = 1; x < _pluto_canvas.cwidth / count; x += density)
    {
        for (y = 1; y < _pluto_canvas.cheight; y += density)
        {
            int r = x / y;
            int xp = r * x;
            int yp = r * y;
            pluto_set_pix(xp, yp);
            pluto_set_pix_colour(xp, yp, 94, 129, 172);
        }
    }
    pluto_write_out();
    fputs((char *)_pluto_canvas.buffer, fp);	// Write buffer to file
    fclose(fp);

    pluto_deinit();
}
