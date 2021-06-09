#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H
#include <stdbool.h>

typedef unsigned char uchar;
typedef struct
{
    bool antialias;		// If not 0, use anti-antialiasing
    int height, width;		// Height and width of the terminal in chars
    int cheight, cwidth;	// Height and width in pixels
    int bufsize, bmsize;	// Bitmap and buffer sizes
    uchar fg;			// Standard colour fg

    uchar *bitmap;		// Bitmap buffer
    uchar *buffer;		// UTF-8 output buffer
    bool is_init;
} pluto_lib_t;

typedef struct
{
    int x, y;
} pt_t;
/* Origin: (0x, 0y) */

extern pluto_lib_t _pluto_canvas;
/* Instance */

extern void pluto_init_window(bool antialias, uchar fg);
/* Initialize library:
 * Parameters:
 * 	- bool antialias: use antialiased lines ?
 * 	- uchar fr: foreground red
 * 	- uchar fg: foreground green
 * 	- uchar fb: foreground blue
 */

extern void pluto_write_frame();
/* Write a frame to stdout */

extern void pluto_clear();
/* Clear both buffers and the screen */

extern void pluto_deinit();
/* Free resources and restore states */

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

#endif
