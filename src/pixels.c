#include "pluto.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

const uchar _pluto_pixmap[4][2] = {
    {0x01, 0x08},
    {0x02, 0x10},
    {0x04, 0x20},
    {0x40, 0x80}};

const uint8_t _pluto_dinis[4][2] = {
    {0, 3},
    {1, 4},
    {2, 5},
    {6, 7}};

void pluto_transform_ucp(uchar *ret, uint16_t unichr)
{
    ret[0] = (uchar)(((unichr >> 12) & 0x0F) | 0xE0);
    ret[1] = (uchar)(((unichr >> 6) & 0x3F) | 0x80);
    ret[2] = (uchar)(((unichr)&0x3F) | 0x80);
}

uint8_t pluto_len_block(uint8_t block)
{
    uint8_t c;
    for (c = 0; block; block >>= 1)
    {
        c += block & 1;
    }
    return c;
}

void pluto_set_pix(int x, int y)
{
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] |= _pluto_pixmap[y % 4][x % 2];
}

void pluto_set_pix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    _pluto_canvas.pix_colour[y * (_pluto_canvas.width << 1) + x] = (pluto_colour_t){red, green, blue};
    int block = (y >> 2) * _pluto_canvas.width + (x >> 1);
    int bx = (x >> 1) << 1;
    int by = (y >> 2) << 2;
    int tr = 0, tg = 0, tb = 0, pci;
    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 2; x++)
        {
            if (_pluto_canvas.bitmap[block] & (1 << _pluto_dinis[y][x]))
            {
                pci = (y + by) * (_pluto_canvas.width << 1) + (x + bx);

                tr += _pluto_canvas.pix_colour[pci].r;
                tg += _pluto_canvas.pix_colour[pci].g;
                tb += _pluto_canvas.pix_colour[pci].b;
            }
        }
    }

    uint8_t bl = pluto_len_block(_pluto_canvas.bitmap[block]);

    if (bl == 0)
        tr = 255, tg = 255, tb = 255;

    else
    {
        tr /= bl;
        tg /= bl;
        tb /= bl;
    }
    _pluto_canvas.buf_colour[block] = (pluto_colour_t){tr, tg, tb};
}

void pluto_set_cpix(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    pluto_set_pix(x, y);
    pluto_set_pix_colour(x, y, red, green, blue);
}

void pluto_unset_pix(int x, int y)
{
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] &= ~_pluto_pixmap[y % 4][x % 2];
}

void pluto_write_out()
{
    char buf[20];
    for (int i = 0; i < _pluto_canvas.bmsize; i++)
    {
        sprintf(buf, "\e[38;2;%03u;%03u;%03um", _pluto_canvas.buf_colour[i].r, _pluto_canvas.buf_colour[i].g, _pluto_canvas.buf_colour[i].b);
        strcpy((char *)&_pluto_canvas.buffer[i * 24], buf);
        pluto_transform_ucp(&_pluto_canvas.buffer[i * 24 + 19], PLUTO_PIX_CHAR_OFF + _pluto_canvas.bitmap[i]);
    }
}

void pluto_write_frame()
{
    printf("\e[0;0H\e[%dm", _pluto_canvas.fg);
    int wret = write(STDOUT_FILENO, _pluto_canvas.buffer, _pluto_canvas.bufsize);
    (void)wret;
    fflush(stdout);
}

void pluto_clear()
{
    memset(_pluto_canvas.bitmap, 0, _pluto_canvas.bmsize);
    memset(_pluto_canvas.buffer, 0, _pluto_canvas.bufsize);
    memset(_pluto_canvas.pix_colour, 0, _pluto_canvas.bmsize * 8 * sizeof(pluto_colour_t));
    memset(_pluto_canvas.buf_colour, 255, _pluto_canvas.bmsize * sizeof(pluto_colour_t));
    printf("\e[H\e[2J\e[3J");
}
