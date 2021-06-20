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
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#include "pluto.h"
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

pluto_lib_t _pluto_canvas;

void pluto_sigint(int);
void pluto_sigwinch(int);

bool _pluto_screen_swapped = false;
bool _pluto_resize_req = false;

void pluto_save_screen()
{
    if (!_pluto_screen_swapped)
    {
        fputs("\e[?1049h\e[22;0;0t\e[0m\e[H\e[2J\e[3J", stdout);
        fflush(stdout);
        _pluto_screen_swapped = true;
    }
}

void pluto_restore_screen()
{
    if (_pluto_screen_swapped)
    {
        fputs("\e[0m\e[H\e[2J\e[3J\e[?1049l\e[22;0;0t", stdout);
        fflush(stdout);
        _pluto_screen_swapped = false;
    }
}

void pluto_clear_buffers()
{
    memset(_pluto_canvas.bitmap, 0, _pluto_canvas.bmsize);
    memset(_pluto_canvas.buffer, 0, _pluto_canvas.bufsize);
    strncpy((char*)_pluto_canvas.buffer, "\e[H", 4);
    memset(_pluto_canvas.pix_colour, 255, _pluto_canvas.bmsize * 8 * sizeof(pluto_colour_t));
}

void pluto_clear()
{
    pluto_clear_buffers();
    printf("\e[H\e[2J\e[3J");
}

void pluto_init_window(bool antialias)
{
    pluto_resize();

    pluto_clear_buffers();

    _pluto_canvas.antialias = antialias;
    _pluto_canvas.is_init = true;
    _pluto_canvas.busy = false;

    signal(SIGINT, pluto_sigint);

    setlocale(LC_ALL, "");

    fputs("\e[?25l", stdout);
    fflush(stdout);
}

void pluto_deinit()
{
    if (!_pluto_canvas.is_init)
        return;

    free(_pluto_canvas.buffer);
    free(_pluto_canvas.bitmap);
    free(_pluto_canvas.pix_colour);

    fputs("\e[?25h", stdout);
    fflush(stdout);

    pluto_restore_screen();

    _pluto_canvas.antialias = false;
    _pluto_canvas.is_init = false;
    _pluto_canvas.busy = false;
    _pluto_canvas.bmsize = 0;
    _pluto_canvas.bufsize = 0;
    _pluto_canvas.cwidth = 0;
    _pluto_canvas.cheight = 0;
    _pluto_canvas.width = 0;
    _pluto_canvas.height = 0;
}

void pluto_sigint(int sig)
{
    (void)sig;
    pluto_deinit();
    exit(0);
}

void pluto_resize()
{
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    _pluto_canvas.height = wsize.ws_row;
    _pluto_canvas.width = wsize.ws_col;

    _pluto_canvas.cheight = wsize.ws_row * 4;
    _pluto_canvas.cwidth = wsize.ws_col * 2;

    _pluto_canvas.bmsize = _pluto_canvas.height * _pluto_canvas.width;
    _pluto_canvas.bufsize = _pluto_canvas.bmsize * 22 + _pluto_canvas.height + 3;

    _pluto_canvas.buffer = (uchar *)realloc(_pluto_canvas.buffer, _pluto_canvas.bufsize);
    _pluto_canvas.bitmap = (uchar *)realloc(_pluto_canvas.bitmap, _pluto_canvas.bmsize);
    _pluto_canvas.pix_colour = (pluto_colour_t *)realloc(_pluto_canvas.pix_colour, _pluto_canvas.bmsize * sizeof(pluto_colour_t) * 8);
}
