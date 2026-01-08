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
    for (int i = 0; i < cfg::grid_size.x * cfg::grid_size.y; i++)
    {
        int column = i % cfg::grid_size.x;
        int row = (i - column)/cfg::grid_size.y;
        drawSquareContent(window, position.squares[i], column, row);
    }
}
