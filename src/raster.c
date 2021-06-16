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
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#include "pluto.h"

void pluto_rast_bftri(pt_t p0, pt_t p1, pt_t p2)
{
    float invslope0 = (float)(p1.x - p0.x) / (p1.y - p0.y);
    float invslope1 = (float)(p2.x - p0.x) / (p2.y - p0.y);
    float curx0 = p0.x;
    float curx1 = p0.x;

    for (int sy = p0.y; sy <= p1.y; sy++)
    {
        pluto_draw_line((pt_t){(int)curx0, sy}, (pt_t){(int)curx1, sy});
        curx0 += invslope0;
        curx1 += invslope1;
    }
}

void pluto_rast_tftri(pt_t p0, pt_t p1, pt_t p2)
{
    float invslope0 = (float)(p2.x - p0.x) / (p2.y - p0.y);
    float invslope1 = (float)(p2.x - p1.x) / (p2.y - p1.y);
    float curx0 = p2.x;
    float curx1 = p2.x;

    for (int sy = p2.y; sy > p0.y; sy--)
    {
        pluto_draw_line((pt_t){(int)curx0, sy}, (pt_t){(int)curx1, sy});
        curx0 -= invslope0;
        curx1 -= invslope1;
    }
}

void pluto_rast_tri(pt_t p0, pt_t p1, pt_t p2)
{

    if (p1.y == p2.y)
        pluto_rast_bftri(p0, p1, p2);

    else if (p0.y == p1.y)
        pluto_rast_tftri(p0, p1, p2);

    else
    {
        pt_t p3 = {(int)(p0.x + ((float)(p1.y - p0.y) / (float)(p2.y - p0.y)) * (p2.x - p0.x)), p1.y};
        pluto_rast_bftri(p0, p1, p3);
        pluto_rast_tftri(p1, p3, p2);
    }
}
