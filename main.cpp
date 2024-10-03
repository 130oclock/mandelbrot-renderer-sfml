#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define ShaderFile "mandelbrot.frag"

unsigned int width = 1280;
unsigned int height = 720;

unsigned int maxIterations = 512;

int main() {

    if (!sf::Shader::isAvailable()) {
        std::cout << "error: Shaders are not available." << std::endl;
    }

    sf::Shader shader;

    if (!shader.loadFromFile(ShaderFile, sf::Shader::Fragment)) {
        std::cout << "error: No shader " << ShaderFile << std::endl; 
    }

    sf::ContextSettings settings(24);
    settings.sRgbCapable = true;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Set", sf::Style::Default, settings);

    sf::RectangleShape rect(sf::Vector2f(width, height));

    sf::RenderTexture text;
    text.create(width, height);

    shader.setUniform("u_resolution", sf::Vector2f(width, height));
    shader.setUniform("u_maxIterations", (int)maxIterations);

    text.draw(rect, &shader);
    text.display();

    sf::Sprite sprite(text.getTexture());

    float x = 0, y = 0, z = 1;
    x = -0.761574;
    y = -0.0847596;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float time = clock.getElapsedTime().asSeconds();

        z = 1 / exp(((time / 12) - floor(time / 12)) * 12);

        shader.setUniform("u_center", sf::Vector2f(x, y));
        shader.setUniform("u_zoom", z);

        text.draw(rect, &shader);
        text.display();

        sprite.setTexture(text.getTexture());

        window.draw(sprite);
        window.display();
    }

    return 0;
}

