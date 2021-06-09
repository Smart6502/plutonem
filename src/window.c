#include "pluto.h"
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

pluto_lib_t _pluto_canvas;

void pluto_check()
{
    if (_pluto_canvas.is_init) pluto_deinit();
}

void pluto_init_window(bool antialias, uchar fr, uchar fg, uchar fb)
{
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);

    _pluto_canvas.height = wsize.ws_row;
    _pluto_canvas.width = wsize.ws_col;
    _pluto_canvas.fr = fr;
    _pluto_canvas.fg = fg;
    _pluto_canvas.fb = fb;

    _pluto_canvas.cheight = wsize.ws_row * 4;
    _pluto_canvas.cwidth = wsize.ws_col * 2;
    _pluto_canvas.bmsize = _pluto_canvas.height * _pluto_canvas.width;
    _pluto_canvas.bufsize = _pluto_canvas.bmsize * 3;

    _pluto_canvas.buffer = (uchar *)malloc(_pluto_canvas.bufsize);
    memset(_pluto_canvas.buffer, 0, _pluto_canvas.bufsize);

    _pluto_canvas.bitmap = (uchar *)malloc(_pluto_canvas.bmsize);
    memset(_pluto_canvas.bitmap, 0, _pluto_canvas.bmsize);

    _pluto_canvas.antialias = antialias;
    _pluto_canvas.is_init = true;
    atexit(pluto_check);
    signal(SIGINT, pluto_check);

    setlocale(LC_ALL, "");
    printf("\e[?25l\e[0;0H\e[38;2;%d;%d;%dm", _pluto_canvas.fr, _pluto_canvas.fg, _pluto_canvas.fb);
}

void pluto_deinit()
{
    free(_pluto_canvas.buffer);
    free(_pluto_canvas.bitmap);
    printf("\e[%d;%dH\e[?25h\n", _pluto_canvas.height, _pluto_canvas.width);

    _pluto_canvas.antialias = false;
    _pluto_canvas.is_init = false;
    _pluto_canvas.bmsize = 0;
    _pluto_canvas.bufsize = 0;
    _pluto_canvas.cwidth = 0;
    _pluto_canvas.cheight = 0;
    _pluto_canvas.width = 0;
    _pluto_canvas.height = 0;
}
