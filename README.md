# plutonem

<p> A library to draw pixels in the terminal </p>

### Building
Plutonem supports a variety of options <br>

- ERROR_CHECK - checks for errors in functions (reduces performance) <br>

- SPACE_CLEAR - clears the screen with spaces instead of the \u2800 Unicode character (increases performance) <br>

- PLUTO_EXTRAS - extra functions <br>

All of these can be un/opted in the Makefile CFLAGS

### Using the library

1. Include the pluto header in your source file
```
#include <path to pluto.h>
```

2. Write your source code. An example program which draws a line:
```
// program.c
#include "pluto.h"

int main()
{
    struct pluto_struct_t demo;

    pluto_init_mode(&demo);                 // Initializes pluto
    pluto_clear(&demo);                     // Clears the screen
    pluto_draw_line(&demo, 5, 10, 20, 25);  // Draws a line from (5x, 10y) to (20x, 25y)
    pluto_close_mode(&demo);                // Closes pluto

    return 0;
}
```

3. Link all of the library object files generated, for example:
```
gcc -c program.c -o program.o
gcc -o program program.o <path/s to library object/s>
```

4. You're done! Just run your program now!

<p>Example shapes in space mode</p>
<img src="shapes_space_mode.png" align="center">
<br>
<p>Accuracy of the pixel drawing (noclear mode)</p>
<img src="shapes_nospace_clear.png" align="center">

### Troubleshooting

1. Check if proper fonts are installed. Pluto uses Unicode characters from `\u2800` to `\u28FF`
2. Check if your terminal supports Unicode
3. Idk
