#include <math.h>
#include <iostream>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "fractal.h"

float zoomFunc(float zoom)
{
    return 1 / exp(zoom);
}

Fractal::Fractal(std::string shaderPath, unsigned int width, unsigned int height, unsigned int maxIterations)
    : width{width}, height{height}, maxIterations{maxIterations}, x{0}, y{0}, z{-0.694}, zoomRate{0.375}
{
    if (!shader.loadFromFile(shaderPath, sf::Shader::Fragment))
    {
        std::cout << "error: No shader found at " << shaderPath << std::endl;
        exit(1);
    }

    setResolution(width, height);
    setMaxIterations(maxIterations);
}

void Fractal::draw(sf::RenderWindow &window)
{
    sf::RectangleShape screen(sf::Vector2f(width, height));

    shader.setUniform("u_center", sf::Vector2f(x, y));
    shader.setUniform("u_zoom", zoomFunc(z));

    window.draw(screen, &shader);
}

void Fractal::zoom(float elapsedTime)
{
    z += elapsedTime * zoomRate;
}

void Fractal::move(sf::Vector2i mousePosition, float elapsedTime)
{
    float mx = zoomFunc(z) * (float(mousePosition.x << 1) - width) / width;
    float my = zoomFunc(z) * -(float(mousePosition.y << 1) - height) / width;

    x += elapsedTime * mx;
    y += elapsedTime * my;
}

void Fractal::setResolution(unsigned int width, unsigned int height)
{
    width = width;
    height = height;
    shader.setUniform("u_resolution", sf::Vector2f(width, height));
}

void Fractal::setMaxIterations(unsigned int maxIterations)
{
    maxIterations = maxIterations;
    shader.setUniform("u_maxIterations", (int)maxIterations);
}