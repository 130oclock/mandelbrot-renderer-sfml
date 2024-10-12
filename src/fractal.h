#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

float zoomFunc(float zoom);

class Fractal
{
private:
    unsigned int width, height, maxIterations;
    float x, y, z, zoomRate;
    sf::Shader shader;

public:
    Fractal(std::string shaderPath, unsigned int widthIn, unsigned int heightIn, unsigned int maxIterationsIn);

    void draw(sf::RenderWindow &window);

    void zoom(float elapsedTime);
    void move(sf::Vector2i mousePosition, float elapsedTime);

    void setResolution(unsigned int width, unsigned int height);
    void setMaxIterations(unsigned int maxIterations);
};

#endif