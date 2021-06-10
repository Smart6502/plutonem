<img src="screenshots/pluto.png" align="center">

<p> A library to draw graphics with pixels in the terminal </p>

### Building
To generate `libpluto.a`, run:
```
$ make
```
To install it so that gcc can use it directly, run:
```
# make install
```
To compile some examples, run:
```
$ make exp
```

### Using the library

1. Include the pluto header in your source file
```
#include <path to pluto.h> // do #include <pluto.h> if the lib is already installed
```

2. Write your source code. An example program which draws a line:
```
// examples/program.c
#include "pluto.h"
// If you have installed the library, you can do #include <pluto.h>

int main()
{
    pluto_init_window(true, 35);	 	             	// Initializes pluto with anti-aliasing, foreground colour 35
    pluto_draw_line((pt_t){5, 10}, (pt_t){20, 25});	        // Draws a line from (5x, 10y) to (20x, 25y)
    pluto_write_out();						// Writes bitmap to UTF-8 buffer
    pluto_write_frame();					// Writes the UTF-8 buffer to STDOUT
    pluto_deinit();      	                                // De-initializes pluto

    return 0;
}
```

3. Link all of the library object files generated, for example:
```
$ gcc -o program program.c -L<path to the FOLDER where libpluto.a is located> -lpluto  # if you have installed the lib already, there is no need to use -L
```

4. You're done! Just run your program now!

<img src="screenshots/hexagon.png" align="center">
<br>
<p>Depth with pixel density (examples/density.c)</p>
<img src="screenshots/pixel_density.png" align="center">
<br>
<p>Rasterized triangle (examples/raster.c)</p>
<img src="screenshots/raster.png" align="center">
<br>
<p>Conway's Game of Life written using plutonem</p>
<img src="screenshots/conways_game_of_life.png" align="center">

### Things to do (you can contribute)
- [ ] Fix colours
- [ ] Colour RGB (256, 256, 256)
- [ ] Polygons, rasterization 

### Troubleshooting

1. Check if proper fonts are installed. Pluto uses Unicode characters from `\u2800` to `\u28FF`. I recommend the `Cascadia` font for best quality.
2. Check if your terminal supports Unicode
3. Check your locale, lang. I have my locale set to `en_US.UTF-8`. On Arch Linux, which I use, I would use this command to set it:
```
# localectl set-locale LANG=en_US.UTF-8
```
4. Idk
