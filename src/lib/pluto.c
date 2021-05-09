#include "pluto.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

const uint8_t pluto_pixmap[4][2] = {
    [0] = {0x01, 0x08},
    [1] = {0x02, 0x10},
    [2] = {0x04, 0x20},
    [3] = {0x40, 0x80}};
struct termios pluto_mode_term, pluto_mode_restore;
void pluto_init_mode(struct pluto_struct_t *__ret)
{
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    __ret->height = wsize.ws_row;
    __ret->width = wsize.ws_col;
    __ret->in_use = 1;

    __ret->buffer = (uint8_t **)malloc(__ret->height * sizeof(uint8_t *));
    for (int i = 0; i < __ret->height; i++)
        __ret->buffer[i] = (uint8_t *)malloc(__ret->width * sizeof(uint8_t));
    printf("Created buffer of size %d\n", __ret->height * __ret->width);

    tcgetattr(0, &pluto_mode_term);
    tcgetattr(0, &pluto_mode_restore);
    pluto_mode_term.c_iflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &pluto_mode_term);
    setlocale(LC_ALL, "");
    
    printf("%d %d\n", __ret->height, __ret->width);
}

void pluto_close_mode(struct pluto_struct_t *__close)
{
    for (int i = 0; i < __close->height; i++)
        free(__close->buffer[i]);
    free(__close->buffer);

    printf("\e[%d;%dH", __close->height, __close->width);
    tcsetattr(0, TCSANOW, &pluto_mode_restore);

    __close->height = 0;
    __close->width = 0;
    __close->in_use = 0;
    fflush(stdout);
}

void pluto_write_pix(struct pluto_struct_t *__info, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    __info->buffer[cy][cx] |= pluto_pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, PLUTO_PIX_CHAR_OFF + __info->buffer[cy][cx]);
}

void pluto_del_pix(struct pluto_struct_t *__info, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    __info->buffer[cy][cx] &= ~pluto_pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, PLUTO_PIX_CHAR_OFF + __info->buffer[cy][cx]); // TODO: fix remanants after complete deletion of block
}

void pluto_clear(struct pluto_struct_t *__info)
{
    for (int bh = 0; bh < __info->height; bh++)
    {
        for (int bw = 0; bw < __info->width; bw++)
        {
            __info->buffer[bh][bw] = 0;
            #ifndef SPACE_CLEAR
            printf("\e[%d;%dH\u2800", bh, bw);
            #else
            printf("\e[%d;%dH ", bh, bw);
            #endif
        }
    }
    fflush(stdout);
}

static int pluto_abs(int i) { return (i < 0) ? -i : i; }
void pluto_draw_line(struct pluto_struct_t *__info, int x0, int y0, int x1, int y1)
{
    #ifdef ERROR_CHECK
    if (x0 < 0 || y0 < 0 || __info->width * 2 < x1 || __info->height * 4 < y1) return;
    #endif
    int dx = pluto_abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = pluto_abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        pluto_write_pix(__info, x0, y0);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
    fflush(stdout);
}