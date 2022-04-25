#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <src/Window/Implementations/SFML/SFMLWindow.hpp>

int main()
{
    SFMLWindow myWindow;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    const auto clearColor = sf::Color::Black;

    while (window.isOpen()) {
        window.clear(clearColor);   

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.display();
    }

    return 0;
}
