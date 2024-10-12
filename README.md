# Mandelbrot Set Renderer

<p align="center">
    <img src="docs/images/Mandelbrot_set_window.png?raw=true" alt="The Mandelbrot Set drawn in a window." width="70%"/><br>
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License MIT">
    <img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/130oclock/mandelbrot-renderer-sfml">
    <img alt="Language C++" src="https://img.shields.io/badge/language-C%2B%2B-blue">
    <img alt="SFML" src="https://img.shields.io/badge/SFML-8CC841">
</p>

* [Description](#description)
* [Requirements](#requirements)
* [Building](#building)
* [Execution](#execution)

## Description

This project is a Mandelbrot set rendering program written in C++. The window is created and rendered using
the SFML library and GLSL.

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
cmake ..
make main
./bin/main
```

## Execution

Running the program should open a window titled "Mandelbrot Set" which displays the entire Mandelbrot set.
Using the up and down arrow keys will zoom in or out towards your mouse cursor.

If your device does not support shaders, it will exit without opening a window.
