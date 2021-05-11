#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H

typedef struct
{
    int height, width;
    int cheight, cwidth;
    unsigned char **buffer;
} pluto_canvas_t;

typedef struct
{
    int x, y;
} pt_t;

#ifndef PLUTO_PIX_CHAR_OFF
#define PLUTO_PIX_CHAR_OFF
#endif
extern pluto_canvas_t *pluto_init_canvas();
extern void pluto_free_canvas(pluto_canvas_t *canvas);
extern void pluto_set_pix(pluto_canvas_t *canvas, int posx, int posy);
extern void pluto_unset_pix(pluto_canvas_t *canvas, int posx, int posy);
extern void pluto_write_pix(pluto_canvas_t *canvas, int posx, int posy);
extern void pluto_del_pix(pluto_canvas_t *canvas, int posx, int posy);
extern void pluto_draw_canvas(pluto_canvas_t *canvas);
extern void pluto_clear(pluto_canvas_t *canvas);
extern void pluto_draw_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1);
typedef unsigned char uchar;
#endif
