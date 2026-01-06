
#include <SFML/Graphics.hpp>
#include <optional>

#include "input.hpp"

void processEvents(sf::Window& window, Input& input)
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {   
                input.leftPressed = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {   
                input.rightPressed = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {   
                input.downPressed = true;
            }
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (keyPressed->button == sf::Mouse::Button::Left)
                input.mouseClicked = true;
        }
        else if (const auto* keyReleased = event->getIf<sf::Event::MouseButtonReleased>())
        {
            if (keyReleased->button == sf::Mouse::Button::Left)
                input.mouseReleased = true;
        }
    }   
}

