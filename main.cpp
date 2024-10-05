#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define ShaderFile "mandelbrot.frag"
#define zoomRate 0.025

unsigned int width = 1280;
unsigned int height = 720;

unsigned int maxIterations = 1024;

int main()
{

    if (!sf::Shader::isAvailable())
    {
        std::cout << "error: Shaders are not available." << std::endl;
    }

    sf::Shader shader;

    if (!shader.loadFromFile(ShaderFile, sf::Shader::Fragment))
    {
        std::cout << "error: No shader " << ShaderFile << std::endl;
    }

    sf::ContextSettings settings(24);
    settings.sRgbCapable = true;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Set", sf::Style::Default, settings);

    sf::RectangleShape rect(sf::Vector2f(width, height));

    shader.setUniform("u_resolution", sf::Vector2f(width, height));
    shader.setUniform("u_maxIterations", (int)maxIterations);

    float x = 0, y = 0, z = 1;
    x = -0.7615740;
    y = -0.0847596;
    //x = -0.74364085;
    //y = 0.13182733;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float time = clock.getElapsedTime().asSeconds();
        z = time * 0.5;

        shader.setUniform("u_center", sf::Vector2f(x, y));
        shader.setUniform("u_zoom", 1 / exp(z));

        window.draw(rect, &shader);
        window.display();
    }

    return 0;
}
