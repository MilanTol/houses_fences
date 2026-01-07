#pragma once

#include "turn.hpp"
#include "square.hpp"
#include "move.hpp"
#include "../config.hpp"

struct Position
{
    Square squares[cfg::grid_size.x * cfg::grid_size.y];
    Turn turn;

    //simplify looking up squares by using "at" function.
    inline Square& at(int column, int row) 
    {
        return squares[column + row*cfg::grid_size.x];
    }

    Position()
    {
        for (int column = 0; column < cfg::grid_size.x; column++)
        {
            for (int row = 0; row < cfg::grid_size.y; row++)
            {
                at(column, row) = Square();
            }
        }
    }

    void buildHouse(Move& move)
    {
        squares[move.square_id].house = turn.current;
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
                    if (at(column, row).fence == turn.other)
                        at(column, row).fence = 0;
                }
            }
        }
    }    

    void destroyHouse(Move& move)
    {   
        squares[move.square_id].house = 0;
        squares[move.square_id].fence = turn.current;
        turn.destroy();
        turn.move();
    }
    
    void execMove(Move move)
    {
        if (squares[move.square_id].house == 0 and
            squares[move.square_id].fence != turn.other)
        {
            buildHouse(move);
        }

        else if (squares[move.square_id].house == turn.other and
            squares[move.square_id].fence != turn.other and
            turn.destroy_counter < cfg::max_destroy)
        {
            destroyHouse(move);
        }
    }

};