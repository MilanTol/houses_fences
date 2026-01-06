#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../config.hpp"
#include "../graphics/draw_fences_houses.hpp"

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
        if (fence != 0)
            draw_fence(window, fence, column, row);

        if (house != 0)
            draw_house(window, house, column, row);
    }    
};


