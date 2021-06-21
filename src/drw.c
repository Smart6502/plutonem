/* BSD 3-Clause License

Copyright (c) 2021, Smart6502, PQCraft
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
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool _pluto_first_out = true;

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

#define PIX_OOB(x, y) x < 0 || x >= _pluto_canvas.cwidth || y < 0 || y >= _pluto_canvas.cheight

void pluto_set_pix(int x, int y)
{
    if (PIX_OOB(x, y))
        return;
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] |= _pluto_pixmap[y % 4][x % 2];
}

void pluto_set_pix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    if (PIX_OOB(x, y))
        return;
    _pluto_canvas.pix_colour[y * (_pluto_canvas.width << 1) + x] = (pluto_colour_t){red, green, blue};
}

void pluto_set_cpix(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    if (PIX_OOB(x, y))
        return;
    pluto_set_pix(x, y);
    pluto_set_pix_colour(x, y, red, green, blue);
}

void pluto_unset_pix(int x, int y)
{
    if (PIX_OOB(x, y))
        return;
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] &= ~_pluto_pixmap[y % 4][x % 2];
}

void pluto_write_out()
{
    _pluto_canvas.busy = true;
    char buf[20];
    uchar *cbuf = (uchar *)&_pluto_canvas.buffer[3];
    for (int32_t i = 0; i < _pluto_canvas.bmsize; i++)
    {
        int bx = (i % _pluto_canvas.width) * 2;
        int by = (i / _pluto_canvas.width) * 4;
        int tr = 0, tg = 0, tb = 0, pci;

        uint8_t bl = 0;

        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 2; x++)
            {
                if (_pluto_canvas.bitmap[i] & (1 << _pluto_dinis[y][x]))
                {
                    pci = (y + by) * (_pluto_canvas.width << 1) + (x + bx);
                    bl++;
                    tr += _pluto_canvas.pix_colour[pci].r;
                    tg += _pluto_canvas.pix_colour[pci].g;
                    tb += _pluto_canvas.pix_colour[pci].b;
                }
            }
        }

        if (_pluto_canvas.antialias)
            bl = 8;

        if (bl)
        {
            tr /= bl;
            tg /= bl;
            tb /= bl;
        }
        else
        {
            tr = 255, tg = 255, tb = 255;
        }

        sprintf(buf, "\e[38;2;%03u;%03u;%03um", (uint8_t)tr, (uint8_t)tg, (uint8_t)tb);
        strcpy((char *)&cbuf[i * 22 + (i / _pluto_canvas.width)], buf);
        pluto_transform_ucp(&cbuf[i * 22 + 19 + (i / _pluto_canvas.width)], PLUTO_CHAR_OFF + _pluto_canvas.bitmap[i]);
    }
    for (int i = 1; i < _pluto_canvas.height; i++)
    {
        cbuf[_pluto_canvas.width * 22 * i + i - 1] = '\n';
    }
    _pluto_canvas.buffer[_pluto_canvas.bufsize - 1] = 0;
    _pluto_canvas.busy = false;
}

void pluto_sigwinch(int);

void pluto_render()
{
    _pluto_canvas.busy = true;
    if (_pluto_first_out && !_pluto_canvas.screen_swapped)
    {
        for (int32_t i = 1; i < _pluto_canvas.height; i++)
            putchar('\n');

        _pluto_first_out = false;
    }
    fputs((char *)_pluto_canvas.buffer, stdout);
    fflush(stdout);
    _pluto_canvas.busy = false;
}
