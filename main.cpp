#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <iomanip>

#define ShaderFile "mandelbrot.frag"
#define zoomRate 0.5

unsigned int width = 1280;
unsigned int height = 720;

unsigned int maxIterations = 512;

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
    // settings.sRgbCapable = true;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Set", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::RectangleShape rect(sf::Vector2f(width, height));

    shader.setUniform("u_resolution", sf::Vector2f(width, height));
    shader.setUniform("u_maxIterations", (int)maxIterations);

    float x = 0, y = 0, z = -0.118;

    shader.setUniform("u_center", sf::Vector2f(x, y));
    shader.setUniform("u_zoom", 1 / exp(z));

    window.draw(rect, &shader);
    window.display();

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

        float elapsed = clock.restart().asSeconds();

        bool update = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            z += elapsed * zoomRate;
            update = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            z -= elapsed * zoomRate;
            update = true;
        }

        float zoom = 1 / exp(z);

        if (update)
        {
            sf::Vector2 localPosition = sf::Mouse::getPosition(window);
            float mx = zoom * (float(localPosition.x << 1) - width) / height;
            float my = zoom * -(float(localPosition.y << 1) - height) / height;

            x += elapsed * mx;
            y += elapsed * my;

            char str[1024];
            sprintf(str, "Mandelbrot Set : (%f, %f)", x, y);

            window.setTitle(str);

            shader.setUniform("u_center", sf::Vector2f(x, y));
            shader.setUniform("u_zoom", zoom);

            window.draw(rect, &shader);
            window.display();
        }
    }

    return 0;
}
