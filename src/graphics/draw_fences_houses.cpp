#include <SFML/Graphics.hpp>

#include "../config.hpp"

void draw_house(sf::RenderWindow& window, int team, sf::Vector2f position)
{
    sf::RectangleShape house_shape(cfg::house_size);
    house_shape.setPosition(position);

    if (team == 1)
        house_shape.setFillColor(sf::Color::Blue);

    else if (team == 2)
        house_shape.setFillColor(sf::Color::Red);

    window.draw(house_shape);
}

void draw_house(sf::RenderWindow& window, int team, int column, int row)
{
    //compute square size
    float stepsize_x = cfg::window_size.x / (cfg::grid_size.x);
    float stepsize_y = cfg::window_size.y / (cfg::grid_size.y);

    sf::Vector2f position;

    //find the right square
    position.x = column * stepsize_x;
    position.y = row * stepsize_y;

    //add discrepancy size of circle and square size
    position.x += (stepsize_x/2 - cfg::house_size.x/2);
    position.y += (stepsize_y/2 - cfg::house_size.y/2);

    draw_house(window, team, position);  
}

void draw_fence(sf::RenderWindow& window, int team, sf::Vector2f position)
{
    sf::RectangleShape fence_shape(cfg::fence_size);
    fence_shape.setPosition(position);

    fence_shape.setFillColor(sf::Color::Black);
    fence_shape.setOutlineThickness(cfg::fence_size.x / 20.0f);

    if (team == 1)
        fence_shape.setOutlineColor(sf::Color::Blue);
    else if (team == 2)
        fence_shape.setOutlineColor(sf::Color::Red);

    window.draw(fence_shape);
}

void draw_fence(sf::RenderWindow& window, int team, int column, int row)
{   
    //compute square size
    float stepsize_x = cfg::window_size.x / (cfg::grid_size.x);
    float stepsize_y = cfg::window_size.y / (cfg::grid_size.y);

    sf::Vector2f position;

    //find the right square
    position.x = column * stepsize_x;
    position.y = row * stepsize_y;

    //add discrepancy size of circle and square size
    position.x += (stepsize_x/2 - cfg::fence_size.x/2);
    position.y += (stepsize_y/2 - cfg::fence_size.y/2);

    draw_fence(window, team, position);
}
