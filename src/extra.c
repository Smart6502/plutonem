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

#include <stdlib.h>
#include "inc/pluto.h"

void pluto__swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
float pluto__abs(float i) { return (i < 0) ? -i : i; }
void pluto__draw_aa_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1)
{
    int steep = pluto__abs(p1.y - p0.y) > pluto__abs(p1.x - p0.x);

    if (steep)
    {
        pluto__swap(&p0.x, &p0.y);
        pluto__swap(&p1.x, &p1.y);
    }
    if (p0.x > p1.x)
    {
        pluto__swap(&p0.x, &p1.x);
        pluto__swap(&p0.y, &p1.y);
    }

    float dx = p1.x - p0.x, dy = p1.y - p0.y;
    float gradient = dy / dx;
    if (dx == 0.0)
        gradient = 1;

    int xpxl0 = p0.x;
    int xpxl1 = p1.x;
    float intersect_y = p0.y;

    if (steep)
    {
        int x;
        for (x = xpxl0; x <= xpxl1; x++)
        {
            PLUTO__WRITE_PIX(canvas, (int)intersect_y, x);
            PLUTO__WRITE_PIX(canvas, (int)intersect_y - 1, x);
            intersect_y += gradient;
        }
    }
    else
    {
        int x;
        for (x = xpxl0; x <= xpxl1; x++)
        {
            PLUTO__WRITE_PIX(canvas, x, (int)intersect_y);
            PLUTO__WRITE_PIX(canvas, x, (int)intersect_y - 1);
            intersect_y += gradient;
        }
    }
}

void pluto__draw_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1)
{
    if (canvas->anti_alias)
    {
        pluto__draw_aa_line(canvas, p0, p1); return;
    }
    int dx = (int)pluto__abs(p1.x - p0.x), sx = p0.x < p1.x ? 1 : -1;
    int dy = (int)pluto__abs(p1.y - p0.y), sy = p0.y < p1.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        PLUTO__WRITE_PIX(canvas, p0.x, p0.y);

        if (p0.x == p1.x && p0.y == p1.y)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            p0.x += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            p0.y += sy;
        }
    }
}

void pluto__rast_bftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2)
{
    float invslope0 = (float)(p1.x - p0.x) / (p1.y - p0.y);
    float invslope1 = (float)(p2.x - p0.x) / (p2.y - p0.y);
    float curx0 = p0.x;
    float curx1 = p0.x;

    for (int sy = p0.y; sy <= p1.y; sy++)
    {
        pluto__draw_line(canvas, (pt_t){(int)curx0, sy}, (pt_t){(int)curx1, sy});
        curx0 += invslope0;
        curx1 += invslope1;
    }
}

void pluto__rast_tftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2)
{
    float invslope0 = (float)(p2.x - p0.x) / (p2.y - p0.y);
    float invslope1 = (float)(p2.x - p1.x) / (p2.y - p1.y);
    float curx0 = p2.x;
    float curx1 = p2.x;

    for (int sy = p2.y; sy > p0.y; sy--)
    {
        pluto__draw_line(canvas, (pt_t){(int)curx0, sy}, (pt_t){(int)curx1, sy});
        curx0 -= invslope0;
        curx1 -= invslope1;
    }
}

void pluto__rast_tri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2)
{

    if (p1.y == p2.y)
        pluto__rast_bftri(canvas, p0, p1, p2);

    else if (p0.y == p1.y)
        pluto__rast_tftri(canvas, p0, p1, p2);

    else
    {
        pt_t p3 = {(int)(p0.x + ((float)(p1.y - p0.y) / (float)(p2.y - p0.y)) * (p2.x - p0.x)), p1.y};
        pluto__rast_bftri(canvas, p0, p1, p3);
        pluto__rast_tftri(canvas, p1, p3, p2);
    }
}

void pluto__plot_circle(pluto_canvas_t *canvas, pt_t p0, pt_t p1)
{
    PLUTO__WRITE_PIX(canvas, p0.x + p1.x, p0.y + p1.y);
    PLUTO__WRITE_PIX(canvas, p0.x - p1.x, p0.y + p1.y);
    PLUTO__WRITE_PIX(canvas, p0.x + p1.x, p0.y - p1.y);
    PLUTO__WRITE_PIX(canvas, p0.x - p1.x, p0.y - p1.y);
    PLUTO__WRITE_PIX(canvas, p0.x + p1.y, p0.y + p1.x);
    PLUTO__WRITE_PIX(canvas, p0.x - p1.y, p0.y + p1.x);
    PLUTO__WRITE_PIX(canvas, p0.x + p1.y, p0.y - p1.x);
    PLUTO__WRITE_PIX(canvas, p0.x - p1.y, p0.y - p1.x);
}

void pluto__draw_circle(pluto_canvas_t *canvas, pt_t p0, int radius)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    pluto__plot_circle(canvas, p0, (pt_t){x, y});

    while (y >= x)
    {
        x++;

        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;

        pluto__plot_circle(canvas, p0, (pt_t){x, y});
    }
}

void pluto__draw_ellipse(pluto_canvas_t *canvas, pt_t p0, int a, int b)
{
    int wx, wy, t;
    int asq = a * a, bsq = b * b;
    int xa, ya;

    PLUTO__WRITE_PIX(canvas, p0.x, p0.y + b);
    PLUTO__WRITE_PIX(canvas, p0.x, p0.y - b);

    wx = 0;
    wy = b;
    xa = 0;
    ya = asq * 2 * b;
    t = asq / 4 - asq * b;

    for (;;)
    {
        t += xa + bsq;

        if (t >= 0)
        {
            ya -= asq * 2;
            t -= ya;
            wy--;
        }

        xa += bsq * 2;
        wx++;

        if (xa >= ya)
            break;

        PLUTO__WRITE_PIX(canvas, p0.x + wx, p0.y - wy);
        PLUTO__WRITE_PIX(canvas, p0.x - wx, p0.y - wy);
        PLUTO__WRITE_PIX(canvas, p0.x + wx, p0.y + wy);
        PLUTO__WRITE_PIX(canvas, p0.x - wx, p0.y + wy);
    }

    PLUTO__WRITE_PIX(canvas, p0.x + a, p0.y);
    PLUTO__WRITE_PIX(canvas, p0.x - a, p0.y);

    wx = a;
    wy = 0;
    xa = bsq * 2 * a;

    ya = 0;
    t = bsq / 4 - bsq * a;

    for (;;)
    {
        t += ya + asq;

        if (t >= 0)
        {
            xa -= bsq * 2;
            t = t - xa;
            wx--;
        }

        ya += asq * 2;
        wy++;

        if (ya > xa)
            break;

        PLUTO__WRITE_PIX(canvas, p0.x + wx, p0.y - wy);
        PLUTO__WRITE_PIX(canvas, p0.x - wx, p0.y - wy);
        PLUTO__WRITE_PIX(canvas, p0.x + wx, p0.y + wy);
        PLUTO__WRITE_PIX(canvas, p0.x - wx, p0.y + wy);
    }
}
