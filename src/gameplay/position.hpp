#pragma once

#include "turn.hpp"
#include "square.hpp"
#include "move.hpp"
#include "../config.hpp"

struct Position
{
    Square squares[cfg::grid_size.x * cfg::grid_size.y];
    Turn turn;

    Position()
    {
        for (int i = 0; i < cfg::grid_size.x * cfg::grid_size.y; i++)
        {
            squares[i] = Square();
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
            for (int i = 0; i < cfg::grid_size.x * cfg::grid_size.y; i++)
            {
                if (squares[i].fence == turn.other)
                    squares[i].fence = 0;
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

    std::array<bool, cfg::grid_size.x * cfg::grid_size.y> legalMoves() 
    {
        std::array<bool, cfg::grid_size.x * cfg::grid_size.y> result;

        for (int i = 0; i < cfg::grid_size.x * cfg::grid_size.y; i++)
        {
            if (squares[i].fence != turn.current and squares[i].house == turn.current)
            {
                //if house is of other player check whether destroy counter is not reached
                if (squares[i].house == turn.other) 
                {
                    result[i] = (turn.destroy_counter < cfg::max_destroy);
                }

                else
                {
                    result[i] = true;
                }

            }

            result[i] = false;
        }

        return result;
    }

};