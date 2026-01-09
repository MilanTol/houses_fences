#include "../gameplay/position.hpp"

constexpr int SCORE_2 = 20;
constexpr int SCORE_3 = 200;
constexpr int SCORE_4 = 10000;

int evaluateLine(const Position& pos, int start, int dx, int dy, int player)
{
    int count = 0;
    int score = 0;

    int x = start % cfg::grid_size.x;
    int y = start / cfg::grid_size.x;

    while (true)
    {
        int nx = x + dx * count;
        int ny = y + dy * count;

        if (nx < 0 || ny < 0 ||
            nx >= cfg::grid_size.x || ny >= cfg::grid_size.y)
            break;

        int idx = ny * cfg::grid_size.x + nx;

        if (pos.squares[idx].house == player)
        {
            count++;
        }
        else
        {
            break;
        }
    }

    if (count == 2) score += SCORE_2;
    else if (count == 3) score += SCORE_3;
    else if (count >= 4) score += SCORE_4;

    return score;
}

int evaluate(const Position& pos)
{
    int me = pos.turn.current;
    int opp = pos.turn.other;

    int score = 0;

    constexpr int directions[4][2] = {
        {1, 0},   // horizontal
        {0, 1},   // vertical
        {1, 1},   // diagonal 
        {1, -1}   // diagonal /
    };

    for (int i = 0; i < cfg::grid_size.x * cfg::grid_size.y; i++)
    {
        if (pos.squares[i].house == 0)
            continue;

        int player = pos.squares[i].house;

        for (auto& d : directions)
        {
            int s = evaluateLine(pos, i, d[0], d[1], player);

            if (player == me)
                score += s;
            else
                score -= s;
        }
    }

    return score;
}
