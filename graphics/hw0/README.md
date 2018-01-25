# Homework Zero

This compiles and runs on the CSIL Linux machines - run `make`  and then use the
resulting `a.out` executable.  You shouldn't need `build.sh`  - that was from me
compiling on OSX, and uses different linking options.

Run `a.out` to get a black 512x512 square canvas.  Run `a.out some.bmp`  to edit
an oldschool bitmap (only BMP files are supported; `Julia.bmp` is a good test if
you don't have one handy).

When running and focused, the program supports the following commands:
 - **Click and Drag:**  Draw some lines with the current color  (as shown in the
   window title).
 - **Number Keys:**  Change the current color.
 - **Save:**  Press `[W]` to save to a file called `SimpleDraw.bmp`.
 - **Clear:**  Press `[space]` to clear the window to black.

Enjoy!
