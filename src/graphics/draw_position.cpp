#include <SFML/Graphics.hpp>

#include "../graphics/draw_fences_houses.hpp"

#include "../gameplay/position.hpp"
#include "../gameplay/square.hpp"

void drawSquareContent(sf::RenderWindow& window, Square square, int column, int row)
{
    if (square.fence != 0)
        draw_fence(window, square.fence, column, row);

    if (square.house != 0)
        draw_house(window, square.house, column, row);
}

void drawPosition(sf::RenderWindow& window, Position& position)
{
    for (int column = 0; column < cfg::grid_size.x; column++)
    {
        for (int row = 0; row < cfg::grid_size.y; row++)
        {
            drawSquareContent(window, position.at(column, row), column, row);
        }
    }
}
