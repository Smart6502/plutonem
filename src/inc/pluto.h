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

#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H

typedef struct
{
    int height, width;											/* Height, width in pixels */
    int cheight, cwidth;										/* Height, width in characters */
    unsigned char **buffer;										/* Buffer which stores pixel states */
    signed char anti_alias;										/* Set to 0 for no anti-aliasing */
} pluto_canvas_t;											/* Pluto's canvas structure */

typedef struct
{
    int x;
    int y;
} pt_t;													/* Point structure */

#ifndef PLUTO_PIX_CHAR_OFF
#define PLUTO_PIX_CHAR_OFF										/* Unicode character offset */
#endif
#ifndef PLUTO__WRITE_PIX
#define PLUTO__WRITE_PIX pluto__write_pix								/* Defines how functions write pixels */
#endif
extern pluto_canvas_t *pluto__init_canvas(signed char anti_alias); 					/* Initializes canvas, anti-aliasing is enabled if anti_alias is not 0 */
extern void pluto__free_canvas(pluto_canvas_t *canvas);		  					/* Frees canvas */

extern void pluto__set_pix(pluto_canvas_t *canvas, int posx, int posy);					/* Sets a pixel in the buffer at (posx, posy) */
extern void pluto__unset_pix(pluto_canvas_t *canvas, int posx, int posy);				/* Unsets a pixel in the buffer at (posx, posy) */
extern void pluto__write_pix(pluto_canvas_t *canvas, int posx, int posy);				/* Sets a pixel in the buffer at (posx, posy) and writes it to the terminal */
extern void pluto__del_pix(pluto_canvas_t *canvas, int posx, int posy);					/* Unsets a pixel in the buffer at (posx, posy) and removes it from the terminal */

extern void pluto__draw_frame(pluto_canvas_t *canvas);							/* Draws the canvas buffer on the terminal */
extern void pluto__draw_area(pluto_canvas_t *canvas, int start_x, int start_y, int height, int width);	/* Draws a specific rectangular area in the canvas buffer on the terminal */
extern void pluto__clear(pluto_canvas_t *canvas);							/* Clears the buffer and the terminal */

extern void pluto__rast_bftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2);			/* Fills a bottom-flat triangle */
extern void pluto__rast_tftri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2);			/* Fills a top-flat triangle */
extern void pluto__rast_tri(pluto_canvas_t *canvas, pt_t p0, pt_t p1, pt_t p2);				/* Fills any kind of triangle, vertices expected in their height's descending order (heighest first, lowest last) */

extern void pluto__draw_line(pluto_canvas_t *canvas, pt_t p0, pt_t p1);					/* Draws a line from point 0 to point 1 */
extern void pluto__draw_ellipse(pluto_canvas_t *canvas, pt_t p0, int a, int b);				/* Draws an ellipse with centre p0, a, b */
extern void pluto__draw_circle(pluto_canvas_t *canvas, pt_t p0, int radius);				/* Draws a circle with centre p0 and radius radius */
typedef unsigned char uchar;
#endif
