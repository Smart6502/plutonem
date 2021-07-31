<img src="screenshots/pluto.png" align="center">

<p> A library to draw graphics with pixels in the terminal </p>

### Who needs a GUI when you have a terminal ?

### Building
To generate `libpluto.a`, run:
```
$ make
```
To install it so that your compiler can use it directly, run:
```
# make install
```
To compile some examples, run:
```
$ make exp
```
Pre-compiled library files are available in the releases tab (only for Linux x86-64)

### Using the library

1. Include the pluto header in your source file
```
#include <path to pluto.h> // do #include <pluto.h> if the lib is already installed
```

2. Write your source code. An example program which draws a line:
Documentation for the library is in src/pluto.h where functions and structures have been commented
```
#include <stdlib.h>
#include "pluto.h"									/* Change path if needed */

int main()
{
    pluto_init_window();								/* Initialize pluto */
    pluto_save_screen();								/* Save screen */

    for (;;)
    {
    	for (int i = 0; i < _pluto_canvas.cheight; i++)
    	{
	    for (int j = 0; j < _pluto_canvas.cwidth; j++)
	    {
	    	pluto_set_cpix(j, i, rand() % 256, rand() % 256, rand() % 256);		/* Set pixel with random colours */
	    }
    	}

	pluto_write_out();								/* Write to output buffer */
	pluto_render();									/* Render the output buffer */
    }

    pluto_deinit();
    return 0;
}
```

3. Link the library generated, for example:
```
$ gcc -o program program.c -lpluto  # install it before or use -L<lib_folder_path>
```

4. You're done! Just run your program now!

Comments in the [pluto.h](https://github.com/smart6502/plutonem/tree/main/src/pluto.h) file describe what each function/data structure does

<p>Perlin noise using plutonem</p>
<img src="screenshots/perlin_noise.png" align="center">
<br>
<p>Mandelbrot (examples/mandelbrot.c)</p>
<img src="screenshots/mandelbrot.png" align="center">
<br>
<p>Image rendered using plutonem</p>
<img src="screenshots/image_viewer.png" align="center">
<br>
<p>A raycaster written with plutonem</p>
<img src="screenshots/fps.png" align="center">

#### Plutonem is tested and works on:
- [x] Operating systems: Linux, BSD, MacOS, (idk windows cuz cringe)
- [x] Terminal emulators: XTerm, Termite, Konsole, GNOME-terminal, Alacritty (best performance) and Kitty

#### Contributing:
- Bug fixes
- Features (don't pull request too many files at once)
- Issue (GitHub issues tab) fixing

### Troubleshooting

1. Check if proper fonts are installed. Pluto uses Unicode characters from `U+10240(10)` to `U+10495(10)`. I recommend the `Cascadia Mono` font.
2. Check if your terminal supports Unicode
3. Check your locale, lang (pluto only supports UTF-8 currently). I have my locale set to `en_US.UTF-8`. On Arch Linux, which I use, I would use this command to set it:
```
# localectl set-locale LANG=en_US.UTF-8
```
4. Open an issue in the issues tab, provide your terminal name, what locale it is set to, and your font
