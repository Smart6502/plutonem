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
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "inc/pluto.h"

const uchar pluto_pixmap[4][2] = {
    {0x01, 0x08},
    {0x02, 0x10},
    {0x04, 0x20},
    {0x40, 0x80}};
pluto_canvas_t *pluto_init_canvas(signed char anti_alias)
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
    return canvas;
}

void pluto_free_canvas(pluto_canvas_t *canvas)
{
    for (int i = 0; i < canvas->cheight; i++)
        free(canvas->buffer[i]);
    free(canvas->buffer);

    printf("\e[%d;%dH\n", canvas->cheight, canvas->cwidth);
    free(canvas);
}

void pluto_set_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    canvas->buffer[posy / 4][posx / 2] |= pluto_pixmap[posy % 4][posx % 2];
}

void pluto_unset_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    canvas->buffer[posy / 4][posx / 2] &= ~pluto_pixmap[posy % 4][posx % 2];
}

void pluto_write_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    canvas->buffer[cy][cx] |= pluto_pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, PLUTO_PIX_CHAR_OFF + canvas->buffer[cy][cx]);
}

void pluto_del_pix(pluto_canvas_t *canvas, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    canvas->buffer[cy][cx] &= ~pluto_pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, (canvas->buffer[cy][cx]) ? PLUTO_PIX_CHAR_OFF + canvas->buffer[cy][cx] : ' ');
}

void pluto_draw_frame(pluto_canvas_t *canvas)
{
    for (int i = 0; i < canvas->cheight; i++)
        for (int j = 0; j < canvas->cwidth; j++)
	    if (canvas->buffer[i][j])
            	printf("\e[%d;%dH%lc", i, j, PLUTO_PIX_CHAR_OFF + canvas->buffer[i][j]);
}

void pluto_draw_area(pluto_canvas_t *canvas, int start_x, int start_y, int height, int width)
{
    for (int i = start_y; i < height; i++)
        for (int j = start_x; j < width; j++)
            if (canvas->buffer[i][j])
		printf("\e[%d;%dH%lc", i, j, PLUTO_PIX_CHAR_OFF + canvas->buffer[i][j]);
}

void pluto_clear(pluto_canvas_t *canvas)
{
    for (int i = 0; i < canvas->cheight; i++)
        for (int j = 0; j < canvas->cwidth; j++)
            canvas->buffer[i][j] = 0;

    printf("\e[H\e[2J\e[3J");
}
