#pragma once

#include "square.hpp"
#include "../config.hpp"

struct Position
{
    Square squares[cfg::grid_size.x][cfg::grid_size.y];

    Position()
    {
        for (int column = 0; column < cfg::grid_size.x; column++)
        {
            for (int row = 0; row < cfg::grid_size.y; row++)
            {
                squares[column][row] = Square();
            }
        }
    }

    
};