#include "pluto.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const uchar _pluto_pixmap[4][2] = {
    { 0x01, 0x08 },
    { 0x02, 0x10 },
    { 0x04, 0x20 },
    { 0x40, 0x80 }};

void unichr_to_utf8(uchar *ret, uint16_t unichr)
{
    ret[0] = (uchar) (((unichr >> 12) & 0x0F) | 0xE0);
    ret[1] = (uchar) (((unichr >>  6) & 0x3F) | 0x80);
    ret[2] = (uchar) (((unichr >>  0) & 0x3F) | 0x80);
}

void pluto_set_pix(int x, int y)
{
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] |= _pluto_pixmap[y % 4][x % 2];
}

void pluto_unset_pix(int x, int y)
{
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] &= ~_pluto_pixmap[y % 4][x % 2];
}

void pluto_write_out()
{
    for (int i = 0; i < _pluto_canvas.bmsize; i++)
        unichr_to_utf8(&_pluto_canvas.buffer[i * 3], PLUTO_PIX_CHAR_OFF + _pluto_canvas.bitmap[i]);
}

void pluto_write_frame()
{
    printf("\e[0;0H");
    write(STDOUT_FILENO, _pluto_canvas.buffer, _pluto_canvas.bufsize);
}

void pluto_clear()
{
    memset(_pluto_canvas.bitmap, 0, _pluto_canvas.bmsize);
    memset(_pluto_canvas.buffer, 0, _pluto_canvas.bufsize);
    printf("\e[H\e[2J\e[3J");
}
