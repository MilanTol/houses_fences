#pragma once

#include "turn.hpp"
#include "square.hpp"
#include "move.hpp"
#include "../config.hpp"

struct Undo {
    int square;
    int oldHouse;
    int oldFence;
    Turn oldTurn;
};

struct Position
{
    Square squares[cfg::grid_size.x * cfg::grid_size.y];
    Turn turn;

    Undo undo;

    Position()
    {
        for (int i = 0; i < cfg::grid_size.x * cfg::grid_size.y; i++)
        {
            squares[i] = Square();
        }
    }

    void buildHouse(const Move& move)
    {
        squares[move.square].house = turn.current;
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

    void destroyHouse(const Move& move)
    {   
        squares[move.square].house = 0;
        squares[move.square].fence = turn.current;
        turn.destroy();
        turn.move();
    }
    
    void makeMove(const Move move)
    {
        if (squares[move.square].house == 0 and
            squares[move.square].fence != turn.other)
        {
            buildHouse(move);
        }

        else if (squares[move.square].house == turn.other and
            squares[move.square].fence != turn.other and
            turn.destroy_counter < cfg::max_destroy)
        {
            destroyHouse(move);
        }

        else
            return;

        undo.square = move.square;
        undo.oldHouse = squares[move.square].house;
        undo.oldFence = squares[move.square].fence;
        undo.oldTurn = turn;
    }

    void undoMove(const Undo& u)
    {
        squares[u.square].house = u.oldHouse;
        squares[u.square].fence = u.oldFence;
        turn = u.oldTurn;
    }

    std::array<bool, cfg::grid_size.x * cfg::grid_size.y> legalMoves() const
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

            else
            {
                result[i] = false;
            }
        }

        return result;
    }

    std::vector<Move> generateMoves() const
    {   
        std::vector<Move> moves;
        auto legal = legalMoves();

        moves.reserve(cfg::grid_size.x * cfg::grid_size.y);
        
        for (char i = 0; i < legal.size(); i++)
        {
            if (legal[i])
                moves.push_back(Move{i});
        }

        return moves;
    }


};