#pragma once
#include <SFML/Graphics.hpp>

namespace cfg
{

sf::Vector2u const window_size = {1000, 1000};
sf::Vector2i const grid_size = {4, 4};

sf::Vector2f const square_size = {window_size.x/grid_size.x, window_size.y/grid_size.y};

sf::Vector2f constexpr house_size = {square_size.x/2, square_size.y/2};
sf::Vector2f constexpr fence_size = {square_size.x/1.5, square_size.y/1.5};

}
