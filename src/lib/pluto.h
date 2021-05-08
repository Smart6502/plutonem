#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H
#include <stdint.h>

struct pluto_struct_t
{
    int height, width;
    uint8_t **buffer;
    int8_t in_use;
};

#ifndef PLUTO_PIX_CHAR_OFF
#    define PLUTO_PIX_CHAR_OFF
#endif
extern int8_t pluto_init_mode(struct pluto_struct_t *__ret);
extern void pluto_close_mode(struct pluto_struct_t *__close);
extern void pluto_write_pix(struct pluto_struct_t *__info, int posx, int posy);
extern void pluto_del_pix(struct pluto_struct_t *__info, int posx, int posy);
extern void pluto_clear(struct pluto_struct_t *__info);
extern void pluto_draw_line(struct pluto_struct_t *__info, int x0, int y0, int x1, int y1);
#endif