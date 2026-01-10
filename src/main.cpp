#include <SFML/Graphics.hpp>

#include "user_interface/events.hpp"
#include "graphics/draw_grid.hpp"
#include "graphics/draw_position.hpp"
#include "user_interface/position_log.hpp"

#include "config.hpp"
#include "gameplay/square.hpp"

#include "engine/evaluation.hpp"

Input input;
Position_Log position_log; 

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({cfg::window_size.x, cfg::window_size.y}), "Let's play tictactoe!");
    window.setFramerateLimit(60);
    

    while (window.isOpen())
    {
        processEvents(window, input);
        position_log.processEvents(window, input);

        window.clear();
        draw_grid(window);
        drawPosition(window, position_log.displayed_position);
        window.display();

    }
}
