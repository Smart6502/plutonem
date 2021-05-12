#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H

typedef struct
{
    int height, width;
    int cheight, cwidth;
    unsigned char **buffer;
    signed char anti_alias;
} pluto_canvas_t;

typedef struct
{
    int x;
    int y;
} pt_t;

typedef struct
{
    int sides;
    double radius, ort;
    pt_t *points;
} polygon_t;

#ifndef PLUTO_PIX_CHAR_OFF
#define PLUTO_PIX_CHAR_OFF
#endif
extern pluto_canvas_t *pluto_init_canvas(signed char anti_alias);
extern void pluto_free_canvas(pluto_canvas_t *canvas);

extern void pluto_set_pix(pluto_canvas_t *canvas, int posx, int posy);
extern void pluto_unset_pix(pluto_canvas_t *canvas, int posx, int posy);

extern void pluto_write_pix(pluto_canvas_t *canvas, int posx, int posy);
extern void pluto_del_pix(pluto_canvas_t *canvas, int posx, int posy);

extern void pluto_draw_frame(pluto_canvas_t *canvas);
extern void pluto_clear(pluto_canvas_t *canvas);
extern void pluto_draw_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1);

extern void pluto_rast_bftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2);
extern void pluto_rast_tftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2);
extern void pluto_rast_tri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2);

extern polygon_t *pluto_new_polygon(int sides, double radius, double ort);
extern void pluto_calc_polygon_verts(polygon_t *polygon);
extern void pluto_draw_polygon(pluto_canvas_t *canvas, polygon_t *polygon, pt_t centre);
extern void pluto_free_polygon(polygon_t *polygon);
typedef unsigned char uchar;
#endif
