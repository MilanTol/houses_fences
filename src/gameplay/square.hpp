#pragma once

#include <iostream>

#include "../team.hpp"

struct Square
{
    int house;
    int fence;

    Square():
        house(0),
        fence(0)
    {}

    void drawContent(sf::RenderWindow& window, int column, int row)
    {
        if (house != none)
            draw_house(window, house, column, row);

        if (fence != none)
            draw_fence(window, fence, column, row);
    } 
       
};