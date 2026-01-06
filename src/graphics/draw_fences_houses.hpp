#pragma once

#include <SFML/Graphics.hpp>

void draw_house(sf::RenderWindow& window, int team, sf::Vector2f position);
void draw_house(sf::RenderWindow& window, int team, int column, int row);
void draw_fence(sf::RenderWindow& window, int team, sf::Vector2f position);
void draw_fence(sf::RenderWindow& window, int team, int column, int row);
