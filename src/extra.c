#include "inc/pluto.h"
#include <math.h>
#include <stdlib.h>

#ifdef ENABLE_LINE_ANTIALIAS
float pluto_abs(float i) { return (i < 0) ? -i : i; }

void pluto_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int pluto_round(float i) { return ((int)i) + 0.5; }
float pluto_fpon(float i) { return (i > 0) ? i - (int)i : i - ((int)i + 1); }

void pluto_draw_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1)
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

#else
static int pluto_abs(int i) { return (i < 0) ? -i : i; }
void pluto_draw_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1)
{
    int dx = pluto_abs(p1.x - p0.x), sx = p0.x < p1.x ? 1 : -1;
    int dy = pluto_abs(p1.y - p0.y), sy = p0.y < p1.y ? 1 : -1;
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
#endif

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
