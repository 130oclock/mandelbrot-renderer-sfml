#include <iostream>
#include <SFML/Graphics.hpp>

#define WIDTH 640u
#define HEIGHT 480u

#define SHADERNAME "mandelbrot_shader.glsl"

int main() {
    // Check that shaders are available on this device.
    if (!sf::Shader::isAvailable()) {
       std::cout << "error: shaders are not available on this device." << std::endl;
       exit(1);
    }

    sf::Shader shader;
    // Check that sfml was able to load the shader.
    if (!shader.loadFromFile(SHADERNAME, sf::Shader::Fragment)) {
        std::cout << "error: " << SHADERNAME << " was not found." << std::endl;
        exit(1);
    }

    shader.setUniform("Width", (float)WIDTH);
    shader.setUniform("Height", (float)HEIGHT);

    auto window = sf::RenderWindow{
        {WIDTH, HEIGHT},
        "Mandelbrot Set"
    };
    window.setFramerateLimit(60);

    auto screen = sf::RectangleShape{sf::Vector2f{window.getSize()}};

    while(window.isOpen()) {
        for (sf::Event event; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(screen, &shader);
        window.display();
    }

    return 0;
}
