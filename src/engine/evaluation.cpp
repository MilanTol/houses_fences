#include "../gameplay/position.hpp"

int houseScore(const Position& position);
int fenceScore(const Position& position);
int mobilityScore(const Position& position);
int destroyPotentialScore(const Position& position);

constexpr int HOUSE_VALUE          = 10;
constexpr int FENCE_VALUE          = 3;
constexpr int MOBILITY_VALUE       = 10;
constexpr int DESTROY_POTENTIAL    = 10;


int evaluate(const Position& pos)
{
    int score = 0;

    score += houseScore(pos);
    score += fenceScore(pos);
    score += mobilityScore(pos);
    score += destroyPotentialScore(pos);

    return score;
}

int houseScore(const Position& pos)
{
    int score = 0;
    const int total = cfg::grid_size.x * cfg::grid_size.y;

    for (int i = 0; i < total; i++)
    {
        if (pos.squares[i].house == pos.turn.current)
            score += HOUSE_VALUE;
        else if (pos.squares[i].house == pos.turn.other)
            score -= HOUSE_VALUE;
    }

    return score;
}

int fenceScore(const Position& pos)
{
    int score = 0;
    const int total = cfg::grid_size.x * cfg::grid_size.y;

    for (int i = 0; i < total; i++)
    {
        if (pos.squares[i].fence == pos.turn.current)
            score += FENCE_VALUE;
        else if (pos.squares[i].fence == pos.turn.other)
            score -= FENCE_VALUE;
    }

    return score;
}

int mobilityScore(const Position& pos)
{
    auto legal = pos.legalMoves();
    int count = 0;

    for (bool m : legal)
        if (m) count++;

    return count * MOBILITY_VALUE;
}

int destroyPotentialScore(const Position& pos)
{
    if (pos.turn.destroy_counter < cfg::max_destroy)
        return DESTROY_POTENTIAL;
    else
        return -DESTROY_POTENTIAL;
}
