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
Pre-compiled library files are available in the releases tab

### Using the library

1. Include the pluto header in your source file
```
#include <path to pluto.h> // do #include <pluto.h> if the lib is already installed
```

2. Write your source code. An example program which draws a line:
```
/* examples/program.c */
#include <stdlib.h>
#include <pluto.h>

int main()
{
    pluto_init_window(false);								/* Initialize pluto without anti-aliasing */
    pluto_save_screen();								/* Save screen (restored later) */

    for (;;)
    {
    	for (int i = 0; i < _pluto_canvas.cheight; i++)
    	{
	    for (int j = 0; j < _pluto_canvas.cwidth; j++)
	    {
	    	pluto_set_cpix(j, i, rand() % 256, rand() % 256, rand() % 256);		/* Set pixel with random colours */
	    }
    	}

	pluto_write_out();								/* Write to outbuffer */
	pluto_render();									/* Render the outbuffer */
    }

    pluto_deinit();
    return 0;
}
```

3. Link the library generated, for example:
```
$ gcc -o program program.c -L<path to the FOLDER where libpluto.a is located> -lpluto  # if you have installed the lib already, there is no need to use -L
```

4. You're done! Just run your program now!

Comments in the pluto.h file describe what each function/data structure does

<p>Perlin noise using plutonem</p>
<img src="screenshots/perlin_noise.png" align="center">
<br>
<p>Mandelbrot (examples/mandelbrot.c)</p>
<img src="screenshots/mandelbrot.png" align="center">
<br>
<p>Image rendered using plutonem</p>
<img src="screenshots/image_viewer.png" align="center">
<br>
<p>A first person shooter using plutonem</p>
<img src="screenshots/fps.png" align="center">

#### Plutonem is tested on:
- [x] Operating systems: Linux, BSD, MacOS
- [x] Terminal emulators: Termite, Konsole

#### To-do
- [x] RGB colours
- [x] Fixing colour darkening
- [ ] Port to Windows
- [ ] More geometry stuff (transforms etc.)

#### Contributing:
- Bug fixes
- Small features (do not pull request a bunch of files together)
- Issue (GitHub issues tab) fixing

### Troubleshooting

1. Check if proper fonts are installed. Pluto uses Unicode characters from `\u2800` to `\u28FF`. I recommend the `Cascadia` font for best quality.
2. Check if your terminal supports Unicode
3. Check your locale, lang (pluto only supports UTF-8 currently). I have my locale set to `en_US.UTF-8`. On Arch Linux, which I use, I would use this command to set it:
```
# localectl set-locale LANG=en_US.UTF-8
```
4. Open an issue in the issues tab, provide your terminal name, what locale it is set to `$(locale)`, your font
