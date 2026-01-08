#include "../gameplay/position.hpp"

int evaluation(Position& position)
{
    int result;

    for (int i = 0; i < cfg::grid_size.y; i++)
    {
    result += rowcontent(position, i);
    }

    return result;
}

int rowcontent(Position& position, int row)
{
    int result; 

    for (int i = 0; i < cfg::grid_size.x; i++)
    {
        if (position.squares[i].house)
            result += 1;

        if (position.squares[i].fence)
            result += 1;
    }

    return result;
}