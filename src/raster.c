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
