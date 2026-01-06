#pragma once

#include "turn.hpp"
#include "square.hpp"
#include "../config.hpp"

struct Position
{
    Square squares[cfg::grid_size.x][cfg::grid_size.y];
    Turn turn;

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

    void drawPosition(sf::RenderWindow& window)
    {
        for (int column = 0; column < cfg::grid_size.x; column++)
        {
            for (int row = 0; row < cfg::grid_size.y; row++)
            {
                squares[column][row].drawContent(window, column, row);
            }
        }
    }

    void buildHouse(int column, int row)
    {
        squares[column][row].house = turn.current;
        destroyFences();
        turn.move();
    }

    void destroyFences()
    {
        if (turn.move_counter == cfg::max_moves - 1 and
            turn.destroy_counter == 0)
        {
            for (int column = 0; column < cfg::grid_size.x; column++)
            {
                for (int row = 0; row < cfg::grid_size.y; row++)
                {
                    if (squares[column][row].fence == turn.other)
                        squares[column][row].fence = 0;
                }
            }
        }
    }    

    void destroyHouse(int column, int row)
    {   
        squares[column][row].house = 0;
        squares[column][row].fence = turn.current;
        turn.destroy();
        turn.move();
    }
    
    void playTurn(int column, int row)
    {   
        if (squares[column][row].house == 0 and
            squares[column][row].fence != turn.other)
        {
            buildHouse(column, row);
        }
        else if (squares[column][row].house == turn.other and
            squares[column][row].fence != turn.other and
            turn.destroy_counter < cfg::max_destroy)
        {
            destroyHouse(column, row);
        }
    }

};