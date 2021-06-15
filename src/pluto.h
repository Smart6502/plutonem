#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H
#include <stdbool.h>
#include <stdint.h>

typedef unsigned char uchar;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pluto_colour_t;

typedef struct
{
    bool antialias;             /* If not 0, use anti-antialiasing */
    int height, width;          /* Height and width of the terminal in chars */
    int cheight, cwidth;        /* Height and width in pixels */
    int bufsize, bmsize;        /* Bitmap and buffer sizes */
    uchar fg;                   /* Standard/fallback colour fg */
    pluto_colour_t *pix_colour; /* 24-bit colour fg */
    uchar *bitmap;              /* Bitmap buffer */
    pluto_colour_t *buf_colour; /* 24-bit colour fg */
    uchar *buffer;              /* UTF-8 output buffer */
    bool is_init;
} pluto_lib_t;

typedef struct
{
    int x, y;
} pt_t;
/* Origin: (0x, 0y) */

#ifndef PLUTO_PIX_CHAR_OFF
#    define PLUTO_PIX_CHAR_OFF /* VSCode keeps complaining lol, so this is the fix */
#endif

extern pluto_lib_t _pluto_canvas;
/* Instance */

extern void pluto_init_window(bool antialias, uchar fg);
/* Initialize library:
 * 	- bool antialias: use antialiased lines ?
 * 	- uchar fg: foreground colour (deprecated)
 */

extern void pluto_write_frame();
/* Write a frame to stdout */

extern void pluto_clear();
/* Clear both buffers and the screen */

extern void pluto_deinit();
/* Free resources and restore states */

extern void pluto_set_pix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
/* Set a pixel's colour to a 24-bit value
 * The colours of the pixels in a block are averaged
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 *  - uint8_t red: red value (0 - 255)
 *  - uint8_t green: green value (0 - 255)
 *  - uint8_t blue: blue value (0 - 255)
 */

extern void pluto_set_cpix(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
/* Set a pixel, and it's colour to a 24-bit value
 * A wrapper for pluto_set_pix and pluto_set_pix_colour
 * Parameters are same as those for pluto_set_pix_colour
 */

extern void pluto_set_pix(int x, int y);
/* Set a pixel in the bitmap buffer:
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 */

extern void pluto_unset_pix(int x, int y);
/* Unset a pixel in the bitmap buffer:
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 */

extern void pluto_write_out();
/* Write bitmap buffer to UTF-8 buffer */

extern void pluto_draw_line(pt_t p0, pt_t p1);
/* Draw a line in the bitmap buffer from p0 to p1 */

extern void pluto_rast_bftri(pt_t p0, pt_t p1, pt_t p2);
/* Rasterize a bottom-flat triangle:
 * 	- pt_t p0: highest point 
 * 	- pt_t p0: lower point 
 * 	- pt_t p0 lowest point
 */

extern void pluto_rast_tftri(pt_t p0, pt_t p1, pt_t p2);
/* Rasterize a top-flat triangle:
 * 	- pt_t p0: highest point 
 * 	- pt_t p0: lower point 
 * 	- pt_t p0 lowest point
 */

extern void pluto_rast_tri(pt_t p0, pt_t p1, pt_t p2);
/* Rasterize any triangle:
 * 	- pt_t p0: highest point 
 * 	- pt_t p0: lower point 
 * 	- pt_t p0 lowest point
 */

extern void pluto_draw_ellipse(pt_t p0, int a, int b);
/* Draw an ellipse
 * 	- pt_t p0: centre
 * 	- int a: a offset
 * 	- int b: b offset
 */

#endif
