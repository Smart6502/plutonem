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

#include "../src/pluto.h"
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* Conway's Game of Life - Standard Game of Life (B3/S23) */

uint8_t *m_out, *m_state;
uint64_t phase_cycles = 0;

int _get_cell(int x, int y)
{
    return m_out[y * _pluto_canvas.cwidth + x];
}

void jump_next_phase()
{
    for (int i = 0; i < _pluto_canvas.cwidth * _pluto_canvas.cheight; i++)
        m_out[i] = m_state[i];

    for (int x = 1; x < _pluto_canvas.cwidth - 1; x++)
    {
        for (int y = 1; y < _pluto_canvas.cheight - 1; y++)
        {
            int n_nb = _get_cell(x - 1, y - 1) + _get_cell(x - 0, y - 1) + _get_cell(x + 1, y - 1) +
                       _get_cell(x - 1, y + 0) + 0 + _get_cell(x + 1, y + 0) +
                       _get_cell(x - 1, y + 1) + _get_cell(x + 0, y + 1) + _get_cell(x + 1, y + 1);

            if (_get_cell(x, y) == 1)
            {
                m_state[y * _pluto_canvas.cwidth + x] = (n_nb == 2 || n_nb == 3);
                pluto_set_pix(x, y);
                if (!m_state[y * _pluto_canvas.cwidth + x])
                {
                    int c = (rand() % 72) + 184;
                    pluto_set_pix_colour(x, y, c, c, c);
                }
                else
                {
                    pluto_set_pix_colour(x, y, 255, 0, 0);
                }
            }
            else
            {
                m_state[y * _pluto_canvas.cwidth + x] = n_nb == 3;
                pluto_unset_pix(x, y);
            }
        }
    }
    pluto_write_out();
    pluto_render();
}

void _setat(int x, int y, char *str)
{
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'R')
        {
            m_state[y * _pluto_canvas.cwidth + x + i] = rand() % 2;
        }
        else
        {
            m_state[y * _pluto_canvas.cwidth + x + i] = str[i] == 'O' ? 1 : 0;
        }
    }
}

void cleanup()
{
    free(m_out);
    free(m_state);
    pluto_deinit();
#if defined(__APPLE__)
    printf("Terminal GOL exited successfully with %llu phase cycles\n", phase_cycles);
#else
    printf("Terminal GOL exited successfully with %ld phase cycles\n", phase_cycles);
#endif
    exit(0);
}

int main()
{
    srand(clock());

    pluto_init_window();
    pluto_save_screen();
    long m_size = _pluto_canvas.cwidth * _pluto_canvas.cheight * sizeof(uint8_t);
    m_out = malloc(m_size);
    m_state = malloc(m_size);
    memset(m_out, 0, m_size);
    memset(m_state, 0, m_size);

    printf("\e[48;2;%u;%u;%um", 20, 32, 52);
    fflush(stdout);

    /* Gosper's Glider */
    _setat(40, 40, "........................O............");
    _setat(40, 41, "......................O.O............");
    _setat(40, 42, "............OO......OO............OO.");
    _setat(40, 43, "...........O...O....OO............OO.");
    _setat(40, 44, "OO........O.....O...OO...............");
    _setat(40, 45, "OO........O...O.OO....O.O............");
    _setat(40, 46, "..........O.....O.......O............");
    _setat(40, 47, "...........O...O.....................");
    _setat(40, 48, "............OO.......................");

    /* Copperhead Spaceship */
    _setat(250, 80, ".OO..OO.");
    _setat(250, 81, "...OO...");
    _setat(250, 82, "...OO...");
    _setat(250, 83, "O.O..O.O");
    _setat(250, 84, "O......O");
    _setat(250, 86, "O......O");
    _setat(250, 87, ".OO..OO.");
    _setat(250, 88, "..OOOO..");
    _setat(250, 90, "...OO...");
    _setat(250, 91, "...OO...");

#define SGG_X 143
    /* Simkin glider gun */
    _setat(SGG_X, 150, "OO.....OO........................");
    _setat(SGG_X, 151, "OO.....OO........................");
    _setat(SGG_X, 153, "....OO...........................");
    _setat(SGG_X, 154, "....OO...........................");
    _setat(SGG_X, 159, "......................OO.OO......");
    _setat(SGG_X, 160, ".....................O.....O.....");
    _setat(SGG_X, 161, ".....................O......O..OO");
    _setat(SGG_X, 162, ".....................OOO...O...OO");
    _setat(SGG_X, 163, "..........................O......");
    _setat(SGG_X, 167, ".................................");
    _setat(SGG_X, 168, ".................................");
    _setat(SGG_X, 169, "................................");
    _setat(SGG_X, 170, ".................................");

    /* MacOS Big Sur */
    _setat(148, 25, "OOOOOOOOO");
    _setat(148, 26, "OOR.O.ROO");
    _setat(148, 27, "OO.RRO.OO");
    _setat(148, 28, "OO.ROR.OO");
    _setat(148, 29, "OO.ORR.OO");
    _setat(148, 30, "OOR.O.ROO");
    _setat(148, 31, "OOOOOOOOO");

    /* Another Gosper's Glider */
    _setat(124, 40, "........................O............");
    _setat(124, 41, "......................O.O............");
    _setat(124, 42, "............OO......OO............OO.");
    _setat(124, 43, "...........O...O....OO............OO.");
    _setat(124, 44, "OO........O.....O...OO...............");
    _setat(124, 45, "OO........O...O.OO....O.O............");
    _setat(124, 46, "..........O.....O.......O............");
    _setat(124, 47, "...........O...O.....................");
    _setat(124, 48, "............OO.......................");

    signal(SIGINT, cleanup);

    //for (int i = 0; i < _pluto_canvas.cwidth * _pluto_canvas.cheight; i++) {
    //    if (!(rand() % 64)) m_state[i] = 1;
    //}

    while (1)
    {
        jump_next_phase();
        phase_cycles++;
        usleep(50000);
    }
    return 0;
}
