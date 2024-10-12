#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>

#define zoomRate 0.5

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

unsigned int maxIterations = 512;

void drawMain(sf::RenderWindow &window, sf::Shader &shader, float x, float y, float z)
{
    sf::RectangleShape screen(sf::Vector2f(windowWidth, windowHeight)); 

    shader.setUniform("u_center", sf::Vector2f(x, y));
    shader.setUniform("u_zoom", 1 / exp(z));

    window.draw(screen, &shader);
}

int main()
{
    // Check if shaders can run on this device.
    if (!sf::Shader::isAvailable())
    {
        std::cout << "error: Shaders are not available on this device." << std::endl;
        exit(1);
    }

    sf::Shader shader;

    std::string shaderPath = "${CMAKE_SOURCE_DIR}/resources/mandelbrot.frag";
    // Check if the desired shader file was opened.
    if (!shader.loadFromFile(shaderPath, sf::Shader::Fragment))
    {
        std::cout << "error: No shader found at " << shaderPath << std::endl;
        exit(1);
    }

    shader.setUniform("u_resolution", sf::Vector2f(windowWidth, windowHeight));
    shader.setUniform("u_maxIterations", (int)maxIterations);

    sf::ContextSettings settings(24);
    // settings.sRgbCapable = true;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mandelbrot Set", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::RectangleShape rect(sf::Vector2f(windowWidth, windowHeight));

    float x = 0, y = 0, z = -0.118;

    drawMain(window, shader, x, y, z);

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
            float mx = zoom * (float(localPosition.x << 1) - windowWidth) / windowHeight;
            float my = zoom * -(float(localPosition.y << 1) - windowHeight) / windowHeight;

            x += elapsed * mx;
            y += elapsed * my;

            // Clear the screen.
            window.clear(sf::Color::Black);

            drawMain(window, shader, x, y, z);

            window.display();
        }
    }

    return 0;
}
