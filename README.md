# Mandelbrot Set Renderer in C++

## Description

This project is a Mandelbrot set rendering program written in C++. The window is created and rendered using
the SFML library and GLSL.

<img style="display: block; margin: auto;" src="docs/images/Mandelbrot_set_window.png?raw=true" alt="The Mandelbrot Set drawn in a window." width="45%"/>

## Requirements

* g++ v12.2 or newer
* CMake v3.25 or newer
* Make

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that directory, and then use `make` to build the desired target.
The compiled program is placed in `build/bin/`.

Example:

```bash
mkdir build
cd build
cmake ../
make main
./bin/main
```

## Execution

If your device supports shaders in SFML, running the program using `./bin/main` should open a window titled "Mandelbrot Set".
It should display the entire Mandelbrot set. Using the up and down arrow keys will zoom in and out towards the mouse cursor respectively.
