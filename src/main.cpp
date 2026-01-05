#include <SFML/Graphics.hpp>

#include "user_interface/events.hpp"
#include "graphics/draw_grid.hpp"

#include "config.hpp"

#include "gameplay/square.hpp"

Input input;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({cfg::window_size.x, cfg::window_size.y}), "Let's play tictactoe!");
    window.setFramerateLimit(60);

    Square square;

    while (window.isOpen())
    {
        processEvents(window, input);
              
        window.clear();
        draw_grid(window);
        
        window.display();
    }
}
