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
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H
#include <stdbool.h>
#include <stdint.h>

typedef unsigned char uchar;

typedef struct
{
    uint8_t r, g, b; /* RGB colour struct */
} pluto_colour_t;

typedef struct
{
    int32_t height, width;         /* Height and width of the terminal in chars */
    int32_t old_height, old_width; /* Old height and width for internal purposes */
    int32_t cheight, cwidth;       /* Height and width in pixels */
    int32_t bufsize, bmsize;       /* Bitmap and buffer sizes */
    pluto_colour_t *pix_colour;    /* 24-bit colour fg */
    uchar *bitmap;                 /* Bitmap buffer */
    uchar *buffer;                 /* UTF-8 output buffer */
    bool screen_swapped;           /* Screen swapped ? */
    bool is_init;                  /* Initialized ? */
    bool busy;                     /* Busy ? */
    bool use_write;
} pluto_lib_t;

#ifndef PLUTO_CHAR_OFF
#    define PLUTO_CHAR_OFF 10240
#endif

extern pluto_lib_t _pluto_canvas;
/* Instance */

extern void pluto_init_window();

extern void pluto_render();
/* Draw frame to stdout */

extern void pluto_write_out();
/* Write bitmap buffer to UTF-8 buffer */

extern void pluto_clear();
/* Clear both buffers and the screen */

extern void pluto_clear_buffers();
/* Clear both buffers only */

extern void pluto_deinit();
/* Free resources and restore states */

/* Pixel functions where 'pix' is prefixed with 'u' are unsafe functions (without bounds checking) */

extern void pluto_set_pix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
/* Set a pixel's colour to a 24-bit value
 * Same as pluto_set_upix_colour()
 */

extern void pluto_set_upix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
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
 * Same as pluto_set_ucpix()
 */

extern void pluto_set_ucpix(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
/* Set a pixel, and it's colour to a 24-bit value
 * A wrapper for pluto_set_pix and pluto_set_pix_colour
 * Parameters are same as those for pluto_set_pix_colour
 */

extern void pluto_set_pix(int x, int y);
/* Set a pixel in the bitmap buffer:
 * Same as pluto_set_upix()
 */

extern void pluto_set_upix(int x, int y);
/* Set a pixel in the bitmap buffer:
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 */

extern void pluto_unset_pix(int x, int y);
/* Unset a pixel in the bitmap buffer:
 * Same as pluto_unset_upix()
 */

extern void pluto_unset_upix(int x, int y);
/* Unset a pixel in the bitmap buffer:
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 */

extern void pluto_save_screen();
/* Saves the screen contents */

extern void pluto_restore_screen();
/* Restores the screen contents */

extern void pluto_resize();
/* Updates the screen and canvas size */

/* Buffer functions */
void pluto_set_buffer_pix(uint8_t *bitmap, int x, int y);
void pluto_unset_buffer_pix(uint8_t *bitmap, int x, int y);
void pluto_set_buffer_pix_colour(pluto_colour_t *buffer, int x, int y, uint8_t red, uint8_t green, uint8_t blue);
void pluto_set_buffer_cpix(uint8_t *bitmap, pluto_colour_t *buffer, int x, int y, uint8_t red, uint8_t green, uint8_t blue);

#endif /* pluto.h */
