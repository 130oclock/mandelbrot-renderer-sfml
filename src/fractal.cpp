#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>

#include "fractal.h"

float zoomFunc(float zoom)
{
    return 1 / exp(zoom);
}

Fractal::Fractal(std::string shaderPath, unsigned int widthIn, unsigned int heightIn, unsigned int maxIterationsIn)
    : width{widthIn}, height{heightIn}, maxIterations{maxIterationsIn}, x{0}, y{0}, z{-0.118}, zoomRate{0.25}
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
    float mx = zoomFunc(z) * (float(mousePosition.x << 1) - width) / height;
    float my = zoomFunc(z) * -(float(mousePosition.y << 1) - height) / height;

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