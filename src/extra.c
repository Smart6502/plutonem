#include "inc/pluto.h"
#include <math.h>
#include <stdlib.h>

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
        pluto_draw_line(canvas, (pt_t){polygon->points[i].x     + centre.x, polygon->points[i].y     + centre.y},
                                (pt_t){polygon->points[i + 1].x + centre.x, polygon->points[i + 1].y + centre.y});
    }
    pluto_draw_line(canvas, (pt_t){polygon->points[0].x                  + centre.x, polygon->points[0].y                  + centre.y},
                            (pt_t){polygon->points[polygon->sides - 1].x + centre.x, polygon->points[polygon->sides - 1].y + centre.y});
}

void pluto_free_polygon(polygon_t *polygon)
{
    free(polygon->points);
    free(polygon);
}