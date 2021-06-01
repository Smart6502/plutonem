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

#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include "inc/pluto.h"

const uchar pluto__pixmap[4][2] = {
    {0x01, 0x08},
    {0x02, 0x10},
    {0x04, 0x20},
    {0x40, 0x80}};
pluto_canvas_t *ccan;
const struct timespec pluto_wres_handle_wait = {
	.tv_sec = 60000 / 1000000,
	.tv_nsec = (60000 % 1000000) * 1000
};

void pluto__dummy_handle()
{
    nanosleep(&pluto_wres_handle_wait, NULL);
}

void pluto__handle_wres()
{
    signal(SIGWINCH, pluto__dummy_handle);
    int tmph = ccan->cheight, tmpw = ccan->cwidth;
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    ccan->cheight = wsize.ws_row;
    ccan->cwidth = wsize.ws_col;
    ccan->height = wsize.ws_row * 4;
    ccan->width = wsize.ws_col * 2;
    ccan->buffer = (unsigned char **)realloc(ccan->buffer, ccan->cheight * sizeof(uchar **));
    for (int i = 0; i < ccan->cheight; i++)
    ccan->buffer[i] = (unsigned char *)realloc(ccan->buffer[i], ccan->cwidth * sizeof(uchar));

    if (tmph < ccan->cheight)
	for (int i = tmph; i < ccan->cheight; i++)
	    for (int j = 0; j < ccan->cwidth; j++)
		ccan->buffer[i][j] = 0;

    if (tmpw < ccan->cwidth)
	for (int i = 0; i < ccan->cheight; i++)
	    for (int j = tmpw; j < ccan->cwidth; j++)
		ccan->buffer[i][j] = 0;

    signal(SIGWINCH, pluto__dummy_handle);
}
pluto_canvas_t *pluto__init_canvas(signed char anti_alias)
{
    pluto_canvas_t *canvas = malloc(sizeof(pluto_canvas_t));
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    canvas->cheight = wsize.ws_row;
    canvas->cwidth = wsize.ws_col;
    canvas->height = wsize.ws_row * 4;
    canvas->width = wsize.ws_col * 2;
    canvas->buffer = (unsigned char **)malloc(canvas->cheight * sizeof(uchar *));
    for (int i = 0; i < canvas->cheight; i++)
        canvas->buffer[i] = (unsigned char *)malloc(canvas->cwidth * sizeof(uchar));

    for (int i = 0; i < canvas->cheight; i++)
        for (int j = 0; j < canvas->cwidth; j++)
            canvas->buffer[i][j] = 0;

    if (!anti_alias)
        canvas->anti_alias = 0;
    else
        canvas->anti_alias = 1;

    setlocale(LC_ALL, "");
    printf("\e[?25l");
    ccan = canvas;
    signal(SIGWINCH, pluto__handle_wres);

    return canvas;
}

void pluto__free_canvas(pluto_canvas_t *canvas)
{
    for (int i = 0; i < canvas->cheight; i++)
        free(canvas->buffer[i]);
    free(canvas->buffer);

    printf("\e[%d;%dH\n", canvas->cheight, canvas->cwidth);
    printf("\e[?25h");
    free(canvas);
}

void pluto__set_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    canvas->buffer[posy / 4][posx / 2] |= pluto__pixmap[posy % 4][posx % 2];
}

void pluto__unset_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    canvas->buffer[posy / 4][posx / 2] &= ~pluto__pixmap[posy % 4][posx % 2];
}

void pluto__write_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    canvas->buffer[cy][cx] |= pluto__pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, PLUTO_PIX_CHAR_OFF + canvas->buffer[cy][cx]);
}

void pluto__del_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    canvas->buffer[cy][cx] &= ~pluto__pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, (canvas->buffer[cy][cx]) ? PLUTO_PIX_CHAR_OFF + canvas->buffer[cy][cx] : ' ');
}

void pluto__draw_frame(pluto_canvas_t *canvas)
{ 
    freopen(NULL, "w", stdout);
    for (int i = 0; i < canvas->cheight; i++)
    {
	wprintf(L"\e[%d;%dH", i, 0);
	for (int j = 0; j < canvas->cwidth; j++)
            putwchar((wchar_t)((canvas->buffer[i][j]) ? PLUTO_PIX_CHAR_OFF + canvas->buffer[i][j] : L' '));
    }
    freopen(NULL, "w", stdout);
}

void pluto__draw_area(pluto_canvas_t *canvas, int start_x, int start_y, int height, int width)
{
    freopen(NULL, "w", stdout);
    for (int i = start_y; i < start_y + height; i++)
    {
	wprintf(L"\e[%d;%dH", i, start_x);
	for (int j = start_x; j < start_x + width; j++)
	    putwchar((wchar_t)((canvas->buffer[i][j] ? PLUTO_PIX_CHAR_OFF + canvas->buffer[i][j] : L' ')));
    }
    freopen(NULL, "w", stdout);
}

void pluto__clear(pluto_canvas_t *canvas)
{
    for (int i = 0; i < canvas->cheight; i++)
        for (int j = 0; j < canvas->cwidth; j++)
            canvas->buffer[i][j] = 0;

    printf("\e[H\e[2J\e[3J");
}
