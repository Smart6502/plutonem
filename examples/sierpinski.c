#include "../src/pluto.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	float x, y;
} point;

const int sx = 10;	// Start X
const int ex = 100;	// End X
const int ty = 10;	// Top Y
const int by = 10;	// Extended bottom Y
const int my = 90;	// Extended max Y
const int iter = 2000;	// Iterations
const int mid = sx + (ex - sx) / 2;

point vx[3] = { {sx, ty}, {ex, ty}, {mid, 0} };
point init = {mid, 0};

void step()
{
	int vt = rand() % 3;

	init = (point){ init.x + (vx[vt].x - init.x) / 2,
			init.y + (vx[vt].y - init.y) / 2 };

	pluto_set_pix(init.x, init.y);
}

void animate()
{
	for (int c = by; c < my; c++)
	{
		vx[2].y = c;
		init.y = (c - vx[0].y) / 2;

		for (int i = 0; i < iter; i++)
			step();

		pluto_write_out();
		pluto_render();
		pluto_clear_buffers();

		usleep(40000);
	}
}

int main()
{
	pluto_init_window();
	
	animate();

	pluto_deinit();

	return 0;
}
