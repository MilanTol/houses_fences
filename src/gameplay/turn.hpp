#pragma once

#include "../config.hpp"

struct Turn
{
    int current = 1;
    int other = 2;
    int move_counter = 1;
    int destroy_counter = 0;

    void end()
    {
        if (current == 1)
        {
            current = 2;
            other = 1;
        }

        else if (current ==2)
        { 
            current = 1;
            other = 2;
        }

        move_counter = 0;
        destroy_counter = 0;
    }

    void move()
    {
        move_counter++;

        if (move_counter >= cfg::max_moves)
        {
            end();
        }
    }

    void destroy()
    {
        destroy_counter++;
    }
};