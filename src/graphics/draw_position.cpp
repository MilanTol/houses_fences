#include <SFML/Graphics.hpp>

#include "../gameplay/position.hpp"

void drawPosition(sf::RenderWindow& window, Position& position)
{
    for (int column = 0; column < cfg::grid_size.x; column++)
    {
        for (int row = 0; row < cfg::grid_size.y; row++)
        {
            position.squares[column][row].drawContent(window, column, row);
        }
    }
}