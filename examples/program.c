#include <pluto.h>
#include <stdlib.h>

int main()
{
    pluto_init_window(false);
    pluto_save_screen();

    for (;;)
    {
        for (int i = 0; i < _pluto_canvas.cheight; i++)
        {
            for (int j = 0; j < _pluto_canvas.cwidth; j++)
            {
                pluto_set_cpix(j, i, rand() % 256, rand() % 256, rand() % 256);
            }
        }

        pluto_write_out();
        pluto_render();
    }

    pluto_deinit();
    return 0;
}
