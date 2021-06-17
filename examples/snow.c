#include <stdio.h>
#include <stdlib.h>
#include "../src/pluto.h"
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

int ws;
float x[256], y[256], f[256], w[256];

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

void pluto_sigwinch(int);

void sigwinch_hndl(int sig) {
    pluto_clear();
    pluto_sigwinch(sig);
}

int main(void) {
    srand(usTime());
    float ws = frand(150) - 75;
    pluto_init_window(false);
    signal(SIGWINCH, sigwinch_hndl);
    for (int i = 0; i < 256; i++) {
        x[i] = (rand() % _pluto_canvas.cwidth);
        y[i] = frand(_pluto_canvas.cheight);
        f[i] = frand(0.15) + 0.25;
        w[i] = (ws / 500) * (frand(1) - 0.5);
    }
    while (1) {
        int cw = (rand() % 16) + 5;
        for (int l = 0; l <= cw; l++) {
            wait_us(35000);
            for (int i = 0; i < 256; i++) {
                pluto_unset_pix((int)x[i], (int)y[i]);
                y[i] += f[i];
                x[i] += w[i];
                uint8_t tmp = (rand() % 72) + 184;
                pluto_set_cpix((int)x[i], (int)y[i], tmp, tmp, tmp);
                if ((int)y[i] >= (_pluto_canvas.cheight - 2) + (rand() % 2)) {
                    x[i] = (rand() % _pluto_canvas.cwidth);
                    y[i] = frand(1);
                    f[i] = frand(0.15) + 0.25;
                    w[i] = ((ws / 500) * (frand(0.25) - 0.125)) + (ws / 500);
                }
            }
            pluto_write_out();
            pluto_render();
            if (!(rand() % 32)) pluto_unset_pix((rand() % _pluto_canvas.cwidth), (_pluto_canvas.cheight - 2) + (rand() % 2));
        }
        ws = frand(150) - 75;
    }
}