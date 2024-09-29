#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#define SHADER_FILE "mandelbrot_shader.glsl"

unsigned int windowWidth = 1280u;
unsigned int windowHeight = 720u;

unsigned int maxIterations = 128u;

void updateRender(sf::RenderWindow *window, sf::Shader *shader, sf::Vector2f center, float zoom)
{
    sf::Vector2u size = window->getSize();

    shader->setUniform("u_resolution", sf::Vector2f{size});
    shader->setUniform("u_maxIterations", (int)maxIterations);

    shader->setUniform("u_center", center);
    shader->setUniform("u_zoom", zoom);

    if (window->isOpen())
    {
        window->clear();

        sf::RectangleShape rect{sf::Vector2f{size}};

        sf::RenderTexture texture;
        texture.create(size.x, size.y);
        texture.draw(rect, shader);
        texture.display();

        sf::Sprite image{texture.getTexture()};

        window->draw(image);
        window->display();
    }
}

int main()
{
    // Check that shaders are available on this device
    if (!sf::Shader::isAvailable())
    {
        std::cout << "error: shaders are not available on this device." << std::endl;
        exit(1);
    }

    sf::Shader shader;
    // Check that sfml was able to load the shader file
    if (!shader.loadFromFile(SHADER_FILE, sf::Shader::Fragment))
    {
        std::cout << "error: " << SHADER_FILE << " was not found." << std::endl;
        exit(1);
    }

    sf::RenderWindow window{sf::VideoMode(windowWidth, windowHeight), "Mandelbrot Set"};
    window.setFramerateLimit(60);

    sf::Vector2f center{0.0, 0.0};
    float zoom = 1.0;

    updateRender(&window, &shader, center, zoom);

    // Run the program while the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window when requested
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
