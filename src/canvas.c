#include "inc/pluto.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

const uchar pluto_pixmap[4][2] = {
    {0x01, 0x08},
    {0x02, 0x10},
    {0x04, 0x20},
    {0x40, 0x80}};

pluto_canvas_t *pluto_init_canvas()
{
    pluto_canvas_t *canvas = malloc(sizeof(pluto_canvas_t));
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    canvas->cheight = wsize.ws_row;
    canvas->cwidth = wsize.ws_col;
    canvas->height = wsize.ws_row * 4;
    canvas->width = wsize.ws_col * 2;

    canvas->buffer = (uchar **)malloc(canvas->cheight * sizeof(uchar *));
    for (int i = 0; i < canvas->cheight; i++)
        canvas->buffer[i] = (uchar *)malloc(canvas->cwidth * sizeof(uchar));

    for (int i = 0; i < canvas->cheight; i++)
    	for (int j = 0; j < canvas->cwidth; j++)
	    canvas->buffer[i][j] = 0;

    setlocale(LC_CTYPE, "en_US.UTF-8");
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
    printf("\e[%d;%dH%lc", cy, cx, PLUTO_PIX_CHAR_OFF + canvas->buffer[cy][cx]); // TODO: fix remanants after complete deletion of block
}

void pluto_draw_canvas(pluto_canvas_t *canvas)
{
    for (int i = 0; i < canvas->cheight; i++)
        for (int j = 0; j < canvas->cwidth; j++)
            printf("\e[%d;%dH%lc", i, j, (canvas->buffer[i][j]) ? PLUTO_PIX_CHAR_OFF + canvas->buffer[i][j] : ' ');
}

void pluto_clear(pluto_canvas_t *canvas)
{
    for (int i = 0; i < canvas->cheight; i++)
	for (int j = 0; j < canvas->cwidth; j++)
	    canvas->buffer[i][j] = 0;

    printf("\e[H\e[2J\e[3J");
    fflush(stdout);
}
