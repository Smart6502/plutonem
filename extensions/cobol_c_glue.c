#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pluto.h"

void pl_init(void) {
    pluto_init_window();
    pluto_save_screen();
}

typedef uint32_t cob_u32_t;
typedef uint8_t cob_u8_t;

#define COBOL_X_TO_C(buf, v, r, s)\
    memcpy(buf, v, s);\
    buf[s] = '\0';\
    r = atoi(buf);\

void pl_cpix(cob_u8_t *x, cob_u8_t *y, cob_u8_t *r, cob_u8_t *g, cob_u8_t *b) {
    uint32_t x8, y8, r8, g8, b8;
    char *tmpbuf;
    
    tmpbuf = malloc(255);
    COBOL_X_TO_C(tmpbuf, x, x8, 3);
    COBOL_X_TO_C(tmpbuf, y, y8, 3);
    COBOL_X_TO_C(tmpbuf, r, r8, 3);
    COBOL_X_TO_C(tmpbuf, g, g8, 3);
    COBOL_X_TO_C(tmpbuf, b, b8, 3);
    free(tmpbuf);

    pluto_set_cpix(x8, y8, r8, g8, b8);
}

void pl_render(void) {
    pluto_write_out();
    pluto_render();
}

void pl_deinit(void) {
    pluto_deinit();
}
