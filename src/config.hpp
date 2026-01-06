#pragma once
#include <SFML/Graphics.hpp>

namespace cfg
{

sf::Vector2u constexpr window_size = {1000, 1000};
sf::Vector2i constexpr grid_size = {4, 4};

sf::Vector2f constexpr square_size = {static_cast<float>(window_size.x/grid_size.x), static_cast<float>(window_size.y/grid_size.y)};

sf::Vector2f constexpr house_size = {static_cast<float>(square_size.x/2.5), static_cast<float>(square_size.y/2.5)};
sf::Vector2f constexpr fence_size = {static_cast<float>(square_size.x/1.5), static_cast<float>(square_size.y/1.5)};

int const max_moves = 2; 
int const max_destroy = 1;

}
