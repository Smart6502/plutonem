#include "inc/pluto.h"
#include <math.h>
#include <stdlib.h>

void pluto_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
float pluto_abs(float i) { return (i < 0) ? -i : i; }
void pluto_draw_aa_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1)
{
    int steep = pluto_abs(p1.y - p0.y) > pluto_abs(p1.x - p0.x);

    if (steep)
    {
        pluto_swap(&p0.x, &p0.y);
        pluto_swap(&p1.x, &p1.y);
    }
    if (p0.x > p1.x)
    {
        pluto_swap(&p0.x, &p1.x);
        pluto_swap(&p0.y, &p1.y);
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
            pluto_write_pix(canvas, (int)intersect_y, x);
            pluto_write_pix(canvas, (int)intersect_y - 1, x);
            intersect_y += gradient;
        }
    }
    else
    {
        int x;
        for (x = xpxl0; x <= xpxl1; x++)
        {
            pluto_write_pix(canvas, x, (int)intersect_y);
            pluto_write_pix(canvas, x, (int)intersect_y - 1);
            intersect_y += gradient;
        }
    }
}

void pluto_draw_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1)
{
    if (canvas->anti_alias)
    {
        pluto_draw_aa_line(canvas, p0, p1);
        return;
    }
    int dx = (int)pluto_abs(p1.x - p0.x), sx = p0.x < p1.x ? 1 : -1;
    int dy = (int)pluto_abs(p1.y - p0.y), sy = p0.y < p1.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        pluto_write_pix(canvas, p0.x, p0.y);

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

void pluto_rast_bftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2)
{
    float invslope0 = (float)(p1.x - p0.x) / (p1.y - p0.y);
    float invslope1 = (float)(p2.x - p0.x) / (p2.y - p0.y);
    float curx0 = p0.x;
    float curx1 = p0.x;

    for (int sy = p0.y; sy <= p1.y; sy++)
    {
        pluto_draw_line(canvas, (pt_t){(int)curx0, sy}, (pt_t){(int)curx1, sy});
        curx0 += invslope0;
        curx1 += invslope1;
    }
}

void pluto_rast_tftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2)
{
    float invslope0 = (float)(p2.x - p0.x) / (p2.y - p0.y);
    float invslope1 = (float)(p2.x - p1.x) / (p2.y - p1.y);
    float curx0 = p2.x;
    float curx1 = p2.x;

    for (int sy = p2.y; sy > p0.y; sy--)
    {
        pluto_draw_line(canvas, (pt_t){(int)curx0, sy}, (pt_t){(int)curx1, sy});
        curx0 -= invslope0;
        curx1 -= invslope1;
    }
}

void pluto_rast_tri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2)
{
    // TODO: sort verts

    if (p1.y == p2.y)
        pluto_rast_bftri(canvas, p0, p1, p2);

    else if (p0.y == p1.y)
        pluto_rast_tftri(canvas, p0, p1, p2);

    else
    {
        pt_t p3 = {(int)(p0.x + ((float)(p1.y - p0.y) / (float)(p2.y - p0.y)) * (p2.x - p0.x)), p1.y};
        pluto_rast_bftri(canvas, p0, p1, p3);
        pluto_rast_tftri(canvas, p1, p3, p2);
    }
}

polygon_t *pluto_new_polygon(int sides, double radius, double ort)
{
    polygon_t *polygon = malloc(sizeof(polygon_t));
    polygon->sides = sides;
    polygon->radius = radius;
    polygon->ort = ort;
    polygon->points = malloc(sizeof(pt_t) * sides);

    pluto_calc_polygon_verts(polygon);

    return polygon;
}

void pluto_calc_polygon_verts(polygon_t *polygon)
{
    double vt;
    for (int i = 0; i < polygon->sides; i++)
    {
        vt = 2 * M_PI * ((double)i / polygon->sides + polygon->ort);
        polygon->points[i].x = round(cos(vt) * polygon->radius);
        polygon->points[i].y = round(sin(vt) * polygon->radius);
    }
}

void pluto_draw_polygon(pluto_canvas_t *canvas, polygon_t *polygon, pt_t centre)
{
    for (int i = 0; i < polygon->sides - 1; i++)
    {
        pluto_draw_line(canvas, (pt_t){polygon->points[i].x + centre.x, polygon->points[i].y + centre.y},
                        (pt_t){polygon->points[i + 1].x + centre.x, polygon->points[i + 1].y + centre.y});
    }
    pluto_draw_line(canvas, (pt_t){polygon->points[0].x + centre.x, polygon->points[0].y + centre.y},
                    (pt_t){polygon->points[polygon->sides - 1].x + centre.x, polygon->points[polygon->sides - 1].y + centre.y});
}

void pluto_free_polygon(polygon_t *polygon)
{
    free(polygon->points);
    free(polygon);
}

void pluto_draw_ellipse(pluto_canvas_t *canvas, pt_t p0, int a, int b)
{
    int wx, wy, t;
    int asq = a * a, bsq = b * b;
    int xa, ya;

    pluto_write_pix(canvas, p0.x, p0.y + b);
    pluto_write_pix(canvas, p0.x, p0.y - b);

    wx = 0;
    wy = b;
    xa = 0;
    ya = asq * 2 * b;
    t = asq / 4 - asq * b;

    for (;;)
    {
        t += xa + bsq;

        if (t >= 0) {
            ya -= asq * 2;
            t -= ya;
            wy--;
        }

        xa += bsq * 2;
        wx++;

        if (xa >= ya)
          break;


        pluto_write_pix(canvas, p0.x + wx, p0.y - wy);
        pluto_write_pix(canvas, p0.x - wx, p0.y - wy);
        pluto_write_pix(canvas, p0.x + wx, p0.y + wy);
        pluto_write_pix(canvas, p0.x - wx, p0.y + wy);
    }

    pluto_write_pix(canvas, p0.x + a, p0.y);
    pluto_write_pix(canvas, p0.x - a, p0.y);

    wx = a;
    wy = 0;
    xa = bsq * 2 * a;

    ya = 0;
    t = bsq / 4 - bsq * a;

    for (;;) {
        t += ya + asq;

        if (t >= 0) {
            xa -= bsq * 2;
            t = t - xa;
            wx--;
        }

        ya += asq * 2;
        wy++;

        if (ya > xa)
          break;

        pluto_write_pix(canvas, p0.x + wx, p0.y - wy);
        pluto_write_pix(canvas, p0.x - wx, p0.y - wy);
        pluto_write_pix(canvas, p0.x + wx, p0.y + wy);
        pluto_write_pix(canvas, p0.x - wx, p0.y + wy);
    }
}
