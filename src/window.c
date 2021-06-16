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

void pluto_init_window(bool antialias)
{
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    _pluto_canvas.height = wsize.ws_row;
    _pluto_canvas.width = wsize.ws_col;

    _pluto_canvas.cheight = wsize.ws_row * 4;
    _pluto_canvas.cwidth = wsize.ws_col * 2;
    _pluto_canvas.bmsize = _pluto_canvas.height * _pluto_canvas.width;
    _pluto_canvas.bufsize = _pluto_canvas.bmsize * 24;

    _pluto_canvas.buffer = (uchar *)malloc(_pluto_canvas.bufsize);
    _pluto_canvas.bitmap = (uchar *)malloc(_pluto_canvas.bmsize);
    _pluto_canvas.pix_colour = (pluto_colour_t *)malloc(_pluto_canvas.bmsize * sizeof(pluto_colour_t) * 8);

    pluto_blank();

    _pluto_canvas.antialias = antialias;
    _pluto_canvas.is_init = true;
    signal(SIGINT, pluto_deinit);

    setlocale(LC_ALL, "");
    printf("\e[?25l\e[0;0H");
}

void pluto_deinit()
{
    if (!_pluto_canvas.is_init)
        return;

    free(_pluto_canvas.buffer);
    free(_pluto_canvas.bitmap);
    free(_pluto_canvas.pix_colour);
    printf("\e[%d;%dH\e[?25h\e[0;0m\n", _pluto_canvas.height, _pluto_canvas.width);

    _pluto_canvas.antialias = false;
    _pluto_canvas.is_init = false;
    _pluto_canvas.bmsize = 0;
    _pluto_canvas.bufsize = 0;
    _pluto_canvas.cwidth = 0;
    _pluto_canvas.cheight = 0;
    _pluto_canvas.width = 0;
    _pluto_canvas.height = 0;
}
