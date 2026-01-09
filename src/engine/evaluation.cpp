#include "../gameplay/position.hpp"

int houseScore(const Position& position);
int fenceScore(const Position& position);
int mobilityScore(const Position& position);
int destroyPotentialScore(const Position& position);

constexpr int HOUSE_VALUE = 10;

int evaluate(const Position& pos)
{
    int score = 0;

    score += houseScore(pos);

    return score;
}

int houseScore(const Position& pos)
{
    int score = 0;
    const int total_squares = cfg::grid_size.x * cfg::grid_size.y;

    if (pos.squares[5].house == pos.turn.current)
        score += HOUSE_VALUE;


    if (pos.squares[6].house == pos.turn.current)
        score += HOUSE_VALUE;


    if (pos.squares[9].house == pos.turn.current)
        score += HOUSE_VALUE;


    if (pos.squares[10].house == pos.turn.current)
        score += HOUSE_VALUE;


    if (pos.squares[5].house == pos.turn.other)
        score -= HOUSE_VALUE;


    if (pos.squares[6].house == pos.turn.other)
        score -= HOUSE_VALUE;


    if (pos.squares[10].house == pos.turn.other)
        score -= HOUSE_VALUE;


    if (pos.squares[11].house == pos.turn.other)
        score -= HOUSE_VALUE;
        

    return score;
}


