#include "inc/pluto.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

const uint8_t pluto_pixmap[4][2] = {
    {0x01, 0x08},
    {0x02, 0x10},
    {0x04, 0x20},
    {0x40, 0x80}};
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

    printf("\e[%d;%dH\n", __close->height, __close->width);
    tcsetattr(0, TCSANOW, &pluto_mode_restore);

    __close->height = 0;
    __close->width = 0;
    __close->in_use = 0;
    fflush(stdout);
}

void pluto_write_pix(struct pluto_struct_t *__info, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    #ifdef ERROR_CHECK
    if (cx > __info->width || cy > __info->height) return;
    #endif
    __info->buffer[cy][cx] |= pluto_pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, PLUTO_PIX_CHAR_OFF + __info->buffer[cy][cx]);
}

void pluto_del_pix(struct pluto_struct_t *__info, int posx, int posy)
{
    int cx = posx / 2, cy = posy / 4;
    #ifdef ERROR_CHECK
    if (cx > __info->width || cy > __info->height) return;
    #endif
    __info->buffer[cy][cx] &= ~pluto_pixmap[posy % 4][posx % 2];
    printf("\e[%d;%dH%lc", cy, cx, PLUTO_PIX_CHAR_OFF + __info->buffer[cy][cx]); // TODO: fix remanants after complete deletion of block
}

void pluto_clear(struct pluto_struct_t *__info)
{
    for (int i = 0; i < __info->height; i++)
    {
        for (int j = 0; j < __info->width; j++)
            __info->buffer[i][j] = 0;
    }    
	printf("\e[H\e[2J\e[3J");
	fflush(stdout);
}