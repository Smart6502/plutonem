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

const uchar _pluto_pixmap[4][2] = {
    {0x01, 0x08},
    {0x02, 0x10},
    {0x04, 0x20},
    {0x40, 0x80}};

#define PIX_OOB(x, y) x < 0 || x >= _pluto_canvas.cwidth || y < 0 || y >= _pluto_canvas.cheight

void pluto_set_pix(int x, int y)
{
    if (PIX_OOB(x, y))
        return;

    pluto_set_upix(x, y);
}

void pluto_set_upix(int x, int y)
{
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] |= _pluto_pixmap[y % 4][x % 2];
}

void pluto_unset_pix(int x, int y)
{
    if (PIX_OOB(x, y))
        return;

    pluto_unset_upix(x, y);
}

void pluto_unset_upix(int x, int y)
{
    _pluto_canvas.bitmap[(y >> 2) * _pluto_canvas.width + (x >> 1)] &= ~_pluto_pixmap[y % 4][x % 2];
}

void pluto_set_pix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    if (PIX_OOB(x, y))
        return;

    pluto_set_upix_colour(x, y, red, green, blue);
}

void pluto_set_upix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    _pluto_canvas.pix_colour[y * (_pluto_canvas.width << 1) + x] = (pluto_colour_t){red, green, blue};
}

void pluto_set_cpix(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    if (PIX_OOB(x, y))
        return;

    pluto_set_ucpix(x, y, red, green, blue);
}

void pluto_set_ucpix(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    pluto_set_upix(x, y);
    pluto_set_upix_colour(x, y, red, green, blue);
}
