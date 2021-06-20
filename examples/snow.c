#include <stdio.h>
#include <stdlib.h>
#include "../src/pluto.h"
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

int ws;
float* x = NULL;
float* y = NULL;
float* f = NULL;
float* w = NULL;
int ct;

struct timeval time1;
uint64_t tval;

uint64_t usTime() {
    gettimeofday(&time1, NULL);
    return time1.tv_sec * 1000000 + time1.tv_usec;
}

#define frand(r) (((float)rand()/(float)(RAND_MAX)) * r)

void wait_us(uint64_t d) {
    #ifdef __unix__
    struct timespec dts;
    dts.tv_sec = d / 1000000;
    dts.tv_nsec = (d % 1000000) * 1000;
    nanosleep(&dts, NULL);
    #else
    uint64_t t = d + usTime();
    while (t > usTime() && !cmdint) {}
    #endif
}

void init_snow() {
    ct = (_pluto_canvas.width * _pluto_canvas.height) / 20;
    x = (float*)realloc(x, ct * sizeof(float));
    y = (float*)realloc(y, ct * sizeof(float));
    f = (float*)realloc(f, ct * sizeof(float));
    w = (float*)realloc(w, ct * sizeof(float));
    for (int i = 0; i < ct; i++) {
        x[i] = (rand() % _pluto_canvas.cwidth);
        y[i] = frand(_pluto_canvas.cheight);
        f[i] = frand(0.2) + 0.20;
        w[i] = (ws / 500) * (frand(1) - 0.5);
    }
}

bool resize_needed = false;

void sigwinch_hndl(int sig) {
    (void)sig;
    resize_needed = true;
}

int main(void) {
    srand(usTime());
    float ws = frand(150) - 75;
    pluto_init_window(false);
    pluto_save_screen();
    signal(SIGWINCH, sigwinch_hndl);
    brk:
    init_snow();
    while (1) {
        int cw = (rand() % 16) + 5;
        for (int l = 0; l <= cw; l++) {
            wait_us(35000);
            for (int i = 0; i < ct; i++) {
                pluto_unset_pix((int)x[i], (int)y[i]);
                y[i] += f[i];
                x[i] += w[i];
                uint8_t tmp = (rand() % 100) + 156;
                pluto_set_cpix((int)x[i], (int)y[i], tmp, tmp, tmp);
                if ((int)y[i] >= (_pluto_canvas.cheight - 2) + (rand() % 2)) {
                    x[i] = (rand() % _pluto_canvas.cwidth);
                    y[i] = frand(1);
                    f[i] = frand(0.2) + 0.20;
                    w[i] = ((ws / 500) * (frand(0.25) - 0.125)) + (ws / 500);
                }
            }
            pluto_write_out();
            pluto_render();
            if (rand() % 2) pluto_unset_pix((rand() % _pluto_canvas.cwidth), _pluto_canvas.cheight - 2);
            if (resize_needed) {
                pluto_resize();
                pluto_clear();
                resize_needed = false;
                goto brk;
            }
        }
        ws = frand(150) - 75;
    }
}
