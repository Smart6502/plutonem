/* BSD 3-Clause License

Copyright (c) 2021, Smart6502
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "pluto.h"
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* Standard Game of Life (B3/S23) */

pluto_canvas_t *canvas;
uint8_t *m_out, *m_state;
uint64_t phase_cycles = 0;
const int wait_t = 80000;
const struct timespec wts = {
	.tv_sec = wait_t / 1000000,
	.tv_nsec = (wait_t % 1000000) * 1000
};

int _get_cell(int x, int y)
{
    return m_out[y * canvas->width + x];
}

void jump_next_phase()
{
    for (int i = 0; i < canvas->width * canvas->height; i++)
	m_out[i] = m_state[i];
    

    for (int x = 1; x < canvas->width - 1; x++)
    {
	for (int y = 1; y < canvas->height - 1; y++)
	{
	     int n_nb = _get_cell(x - 1, y - 1) + _get_cell(x - 0, y - 1) + _get_cell(x + 1, y - 1) +
		     	_get_cell(x - 1, y + 0) + 	     0		  + _get_cell(x + 1, y + 0) +
			_get_cell(x - 1, y + 1) + _get_cell(x + 0, y + 1) + _get_cell(x + 1, y + 1);

	     if (_get_cell(x, y) == 1)
	     {
		 m_state[y * canvas->width + x] = n_nb == 2 || n_nb == 3;
		 pluto__set_pix(canvas, x, y);
	     }
	     else
	     {
		 m_state[y * canvas->width + x] = n_nb == 3;
		 pluto__unset_pix(canvas, x, y);
	     }
	}
    }
    pluto__draw_frame(canvas);
}

void _setat(int x, int y, char *str)
{
    for (unsigned long i = 0; i < strlen(str); i++)
	m_state[y * canvas->width + x + i] = str[i] == '#' ? 1 : 0;
}

void cleanup()
{
    free(m_out);
    free(m_state);
    pluto__clear(canvas);
    pluto__free_canvas(canvas);
    printf("\e[2;0HTerminal GOL exited successfully with %ld phase cycles\n", phase_cycles);
    exit(0);
}


int main()
{
    canvas = pluto__init_canvas(0);
    pluto__clear(canvas);
    long m_size = canvas->width * canvas->height * sizeof(uint8_t);
    m_out = malloc(m_size);
    m_state = malloc(m_size);
    memset(m_out, 0, m_size);
    memset(m_state, 0, m_size);

    /* Gosper's Glider */
    _setat(40, 40, "........................#............");
    _setat(40, 41, "......................#.#............");
    _setat(40, 42, "............##......##............##.");
    _setat(40, 43, "...........#...#....##............##.");
    _setat(40, 44, "##........#.....#...##...............");
    _setat(40, 45, "##........#...#.##....#.#............");
    _setat(40, 46, "..........#.....#.......#............");
    _setat(40, 47, "...........#...#.....................");
    _setat(40, 48, "............##.......................");

    /*for (int i = 0; i < canvas->width * canvas->height; i++)
	    m_state[i] = rand() % 2;*/

    /* Copperhead Spaceship */
    _setat(250, 80, ".##..##.");
    _setat(250, 81, "...##...");
    _setat(250, 82, "...##...");
    _setat(250, 83, "#.#..#.#");
    _setat(250, 84, "#......#");
    _setat(250, 86, "#......#");
    _setat(250, 87, ".##..##.");
    _setat(250, 88, "..####..");
    _setat(250, 90, "...##...");
    _setat(250, 91, "...##...");

    signal(SIGINT, cleanup);

    while (1)
    {
	jump_next_phase();
	phase_cycles++;
	nanosleep(&wts, NULL);
    }
    return 0;
}
