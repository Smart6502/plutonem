#include <algorithm>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#include <X11/Xlib.h>
#include <math.h>
#include <signal.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <termios.h>

extern "C"
{
#include "../src/pluto.h"
}

uint8_t shades[5][3] = {
    {143, 188, 187},
    {136, 192, 208},
    {129, 161, 193},
    {94, 129, 172},
    {76, 86, 106},
};

int n_screen_width = 160;
int n_screen_height = 40;
int n_map_width = 16;
int n_map_height = 16;

float f_player_x = 14.7f;
float f_player_y = 5.09f;
float f_player_a = 0.0f;
float f_fov = M_PI / 4.0f;
float f_depth = 20.0f;
float f_speed = 5.0f;

struct termios tu_term, tu_old_term;
bool tu_textlock = false;

int kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false;
    if (!initialized)
    {
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytes;
    ioctl(STDIN, FIONREAD, &bytes);
    return bytes;
}

void tu_lockTerm()
{
    if (!tu_textlock)
    {
        tcgetattr(0, &tu_term);
        tcgetattr(0, &tu_old_term);
        tu_term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &tu_term);
        tu_textlock = true;
    }
}

void tu_ulock_term()
{
    if (tu_textlock)
    {
        tcsetattr(0, TCSANOW, &tu_old_term);
        tu_textlock = false;
    }
}

Display *g_pDisplay = XOpenDisplay(getenv("DISPLAY"));

bool get_kstate(KeySym keySym)
{
    if (g_pDisplay == NULL)
    {
        return false;
    }

    char szKey[32];
    int iKeyCodeToFind = XKeysymToKeycode(g_pDisplay, keySym);

    XQueryKeymap(g_pDisplay, szKey);

    return szKey[iKeyCodeToFind / 8] & (1 << (iKeyCodeToFind % 8));
}

void c_exit(int sig)
{
    if (sig != SIGINT)
        exit(0);
    tu_ulock_term();
    pluto_clear();
    pluto_deinit();
    fputs("\e[H\e[2J\e[3J", stdout);
    exit(0);
}

int main()
{
    pluto_init_window(true);
    signal(SIGINT, c_exit);

    n_screen_width = _pluto_canvas.cwidth;
    n_screen_height = _pluto_canvas.cheight;

    tu_lockTerm();

    setlocale(LC_CTYPE, "");

    wstring map;
    map += L"#########.......";
    map += L"#...............";
    map += L"#.......########";
    map += L"#..............#";
    map += L"#......##......#";
    map += L"#......##......#";
    map += L"#..............#";
    map += L"###............#";
    map += L"##.............#";
    map += L"#......####..###";
    map += L"#......#.......#";
    map += L"#......#.......#";
    map += L"#..............#";
    map += L"#......#########";
    map += L"#..............#";
    map += L"################";

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();

    bool firstrender = true;

    while (1)
    {
        tp2 = chrono::system_clock::now();
        chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float f_elapsed_time = elapsedTime.count();

        bool render = firstrender;
        firstrender = false;

        if (get_kstate((uint16_t)'A'))
        {
            render = true;
            f_player_a -= (f_speed * 0.75f) * f_elapsed_time;
        }

        if (get_kstate((uint16_t)'D'))
        {
            render = true;
            f_player_a += (f_speed * 0.75f) * f_elapsed_time;
        }

        if (get_kstate((uint16_t)'W'))
        {
            render = true;
            f_player_x += sinf(f_player_a) * f_speed * f_elapsed_time;
            ;
            f_player_y += cosf(f_player_a) * f_speed * f_elapsed_time;
            ;
            if (map.c_str()[(int)f_player_x * n_map_width + (int)f_player_y] == '#')
            {
                f_player_x -= sinf(f_player_a) * f_speed * f_elapsed_time;
                ;
                f_player_y -= cosf(f_player_a) * f_speed * f_elapsed_time;
                ;
            }
        }

        if (get_kstate((uint16_t)'S'))
        {
            render = true;
            f_player_x -= sinf(f_player_a) * f_speed * f_elapsed_time;
            ;
            f_player_y -= cosf(f_player_a) * f_speed * f_elapsed_time;
            ;
            if (map.c_str()[(int)f_player_x * n_map_width + (int)f_player_y] == '#')
            {
                f_player_x += sinf(f_player_a) * f_speed * f_elapsed_time;
                ;
                f_player_y += cosf(f_player_a) * f_speed * f_elapsed_time;
                ;
            }
        }

        for (int x = 0; x < n_screen_width; x++)
        {
            float f_ray_a = (f_player_a - f_fov / 2.0f) + ((float)x / (float)n_screen_width) * f_fov;

            float f_step_size = 0.1f;
            float f_dist_to_wall = 0.0f;

            bool bHitWall = false;
            bool b_bound = false;

            float f_eye_x = sinf(f_ray_a);
            float f_eye_y = cosf(f_ray_a);

            while (!bHitWall && f_dist_to_wall < f_depth)
            {
                f_dist_to_wall += f_step_size;
                int n_test_x = (int)(f_player_x + f_eye_x * f_dist_to_wall);
                int n_test_y = (int)(f_player_y + f_eye_y * f_dist_to_wall);

                if (n_test_x < 0 || n_test_x >= n_map_width || n_test_y < 0 || n_test_y >= n_map_height)
                {
                    bHitWall = true;
                    f_dist_to_wall = f_depth;
                }
                else
                {
                    if (map.c_str()[n_test_x * n_map_width + n_test_y] == '#')
                    {
                        bHitWall = true;
                        vector<pair<float, float>> p;

                        for (int tx = 0; tx < 2; tx++)
                            for (int ty = 0; ty < 2; ty++)
                            {
                                float vy = (float)n_test_y + ty - f_player_y;
                                float vx = (float)n_test_x + tx - f_player_x;
                                float d = sqrt(vx * vx + vy * vy);
                                float dot = (f_eye_x * vx / d) + (f_eye_y * vy / d);
                                p.push_back(make_pair(d, dot));
                            }

                        sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) { return left.first < right.first; });

                        float f_bound = 0.001;
                        if (acos(p.at(0).second) < f_bound)
                            b_bound = true;
                        if (acos(p.at(1).second) < f_bound)
                            b_bound = true;
                        if (acos(p.at(2).second) < f_bound)
                            b_bound = true;
                    }
                }
            }

            int nCeiling = (float)(n_screen_height / 2.0) - n_screen_height / ((float)f_dist_to_wall);
            int nFloor = n_screen_height - nCeiling;

            uint8_t shade_n = 7;
            if (f_dist_to_wall <= f_depth / 4.0f)
                shade_n = 4; // Very close
            else if (f_dist_to_wall < f_depth / 3.0f)
                shade_n = 3;
            else if (f_dist_to_wall < f_depth / 2.0f)
                shade_n = 2;
            else if (f_dist_to_wall < f_depth)
                shade_n = 1;
            else
                shade_n = 0;
            if (b_bound)
                shade_n = 0;

            for (int y = 0; y < n_screen_height; y++)
            {
                if (y <= nCeiling)
                    pluto_set_cpix(x, y, 0, 0, 0);
                else if (y > nCeiling && y <= nFloor)
                    pluto_set_cpix(x, y, shades[shade_n][0], shades[shade_n][1], shades[shade_n][2]);
                else
                {
                    float b = 1.0f - (((float)y - n_screen_height / 2.0f) / ((float)n_screen_height / 2.0f));
                    if (b < 0.25)
                        shade_n = 191;
                    else if (b < 0.5)
                        shade_n = 143;
                    else if (b < 0.75)
                        shade_n = 95;
                    else if (b < 0.9)
                        shade_n = 47;
                    else
                        shade_n = 15;

                    pluto_set_cpix(x, y, shade_n, shade_n, shade_n);
                }
            }
        }

        pluto_write_out();
        if (render)
            pluto_render();
    }

    return 0;
}
