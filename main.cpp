#include <iostream>
#include <SFML/Graphics.hpp>

#define WIDTH 1280u
#define HEIGHT 720u

#define SHADERNAME "mandelbrot_shader.glsl"
#define MAX_ITERATIONS 1024

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

    auto window = sf::RenderWindow{
        {WIDTH, HEIGHT},
        "Mandelbrot Set"
    };
    window.setFramerateLimit(60);

    shader.setUniform("window_Shape", sf::Glsl::Vec2{window.getSize()});
    shader.setUniform("MAX_ITERATIONS", MAX_ITERATIONS);

    auto screen = sf::RectangleShape{sf::Vector2f{window.getSize()}};

    sf::RenderTexture tex;
    tex.create(WIDTH, HEIGHT);
    tex.draw(screen, &shader);
    tex.display();

    sf::Sprite background(tex.getTexture());


    while(window.isOpen()) {
        for (sf::Event event; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(background);
        window.display();
    }

    return 0;
}
