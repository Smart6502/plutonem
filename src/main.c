#include "lib/pluto.h"
#include <stdio.h>

struct pluto_struct_t test;
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
        for (int j = 64; j < 128; j++)
        {
            pluto_write_pix(&test, j, i);
        }
    }
    pluto_close_mode(&test);
    return 0;
}