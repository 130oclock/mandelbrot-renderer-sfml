#include <math.h>
#include <iostream>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "fractal.h"

float zoomFunc(float zoom) { return 1 / exp(zoom); }

Fractal::Fractal(
    std::string shaderFile,
    unsigned int width,
    unsigned int height,
    unsigned int maxIterations)
    : width{width},
      height{height},
      maxIterations{maxIterations},
      x{0}, y{0}, z{-0.694}, zoomRate{0.375}
{
    if (!shader.loadFromFile(shaderFile, sf::Shader::Fragment))
    {
        std::cout << "error: " << shaderFile << " was not found" << std::endl;
        exit(1);
    }

    setResolution(width, height);
    setMaxIterations(maxIterations);
}

void Fractal::update()
{
    shader.setUniform("u_center", sf::Vector2f(x, y));
    shader.setUniform("u_zoom", zoomFunc(z));
}

void Fractal::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, &shader);
}

void Fractal::zoom(float elapsedTime)
{
    z += elapsedTime * zoomRate;
}

void Fractal::move(sf::Vector2i mousePosition, float elapsedTime)
{
    float zoom = zoomFunc(z);
    float mx = zoom * (float(mousePosition.x << 1) - width) / width;
    float my = zoom * -(float(mousePosition.y << 1) - height) / width;

    x += elapsedTime * mx;
    y += elapsedTime * my;
}

void Fractal::setResolution(unsigned int width, unsigned int height)
{
    width = width;
    height = height;
    shape.setSize(sf::Vector2f(width, height));
    shader.setUniform("u_resolution", sf::Vector2f(width, height));
}

void Fractal::setMaxIterations(unsigned int maxIterations)
{
    maxIterations = maxIterations;
    shader.setUniform("u_maxIterations", (int)maxIterations);
}