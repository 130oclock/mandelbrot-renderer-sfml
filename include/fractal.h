#ifndef FRACTAL_H
#define FRACTAL_H

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Fractal : public sf::Drawable
{
private:
    unsigned int width, height, maxIterations;
    float x, y, z, zoomRate;
    sf::Shader shader;
    sf::RectangleShape shape;

public:
    Fractal(
        std::string shaderPath,
        unsigned int width,
        unsigned int height,
        unsigned int maxIterations);

    void update();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void zoom(float elapsedTime);
    void move(sf::Vector2i mousePosition, float elapsedTime);

    void setResolution(unsigned int width, unsigned int height);
    void setMaxIterations(unsigned int maxIterations);
};

#endif