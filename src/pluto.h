#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H
#include <stdbool.h>

typedef unsigned char uchar;
typedef struct
{
    bool antialias;
    int height, width;
    int cheight, cwidth;
    int bufsize, bmsize;

    uchar *bitmap;
    uchar *buffer;
} pluto_canvas_t;

typedef struct
{
    int x, y;
} pt_t;

extern pluto_canvas_t _pluto_canvas;
extern void pluto_init_window(bool antialias);
extern void pluto_write_frame();
extern void pluto_clear();
extern void pluto_deinit();

extern void pluto_set_pix(int x, int y);
extern void pluto_unset_pix(int x, int y);
extern void pluto_write_out();

extern void pluto_draw_line(pt_t p0, pt_t p1);

extern void pluto_rast_bftri(pt_t p0, pt_t p1, pt_t p2);
extern void pluto_rast_tftri(pt_t p0, pt_t p1, pt_t p2);
extern void pluto_rast_tri(pt_t p0, pt_t p1, pt_t p2);

#endif
