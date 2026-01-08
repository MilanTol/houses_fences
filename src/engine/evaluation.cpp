#include "../gameplay/position.hpp"

int houseScore(const Position& position);
int fenceScore(const Position& position);
int mobilityScore(const Position& position);
int destroyPotentialScore(const Position& position);

constexpr int HOUSE_VALUE          = 10;
constexpr int FENCE_VALUE          = 3;
constexpr int MOBILITY_VALUE       = 2;
constexpr int DESTROY_POTENTIAL    = 7;

constexpr int TWO_IN_ROW   = 5;
constexpr int THREE_IN_ROW = 20;
constexpr int FOUR_IN_ROW  = 100;

int scoreRun(int count)
{
    if (count == 2) return TWO_IN_ROW;
    if (count == 3) return THREE_IN_ROW;
    if (count >= 4) return FOUR_IN_ROW;
    return 0;
}

inline int idx(int x, int y)
{
    return y * cfg::grid_size.x + x;
}

int horizontalRuns(const Position& pos)
{
    int score = 0;

    for (int y = 0; y < cfg::grid_size.y; y++)
    {
        int runCurrent = 0;
        int runOther = 0;

        for (int x = 0; x < cfg::grid_size.x; x++)
        {
            int h = pos.squares[idx(x, y)].house;

            if (h == pos.turn.current)
            {
                runCurrent++;
                score -= scoreRun(runOther);
                runOther = 0;
            }
            else if (h == pos.turn.other)
            {
                runOther++;
                score += scoreRun(runCurrent);
                runCurrent = 0;
            }
            else
            {
                score += scoreRun(runCurrent);
                score -= scoreRun(runOther);
                runCurrent = runOther = 0;
            }
        }

        score += scoreRun(runCurrent);
        score -= scoreRun(runOther);
    }

    return score;
}

int verticalRuns(const Position& pos)
{
    int score = 0;

    for (int x = 0; x < cfg::grid_size.x; x++)
    {
        int runCurrent = 0;
        int runOther = 0;

        for (int y = 0; y < cfg::grid_size.y; y++)
        {
            int h = pos.squares[idx(x, y)].house;

            if (h == pos.turn.current)
            {
                runCurrent++;
                score -= scoreRun(runOther);
                runOther = 0;
            }
            else if (h == pos.turn.other)
            {
                runOther++;
                score += scoreRun(runCurrent);
                runCurrent = 0;
            }
            else
            {
                score += scoreRun(runCurrent);
                score -= scoreRun(runOther);
                runCurrent = runOther = 0;
            }
        }

        score += scoreRun(runCurrent);
        score -= scoreRun(runOther);
    }

    return score;
}

int diagonalRuns(const Position& pos)
{
    int score = 0;

    // ↘
    for (int x = 0; x <= cfg::grid_size.x - 4; x++)
    {
        for (int y = 0; y <= cfg::grid_size.y - 4; y++)
        {
            int c = 0, o = 0;
            for (int k = 0; k < 4; k++)
            {
                int h = pos.squares[idx(x + k, y + k)].house;
                if (h == pos.turn.current) c++;
                else if (h == pos.turn.other) o++;
            }
            if (o == 0) score += scoreRun(c);
            if (c == 0) score -= scoreRun(o);
        }
    }

    // ↗
    for (int x = 0; x <= cfg::grid_size.x - 4; x++)
    {
        for (int y = 3; y < cfg::grid_size.y; y++)
        {
            int c = 0, o = 0;
            for (int k = 0; k < 4; k++)
            {
                int h = pos.squares[idx(x + k, y - k)].house;
                if (h == pos.turn.current) c++;
                else if (h == pos.turn.other) o++;
            }
            if (o == 0) score += scoreRun(c);
            if (c == 0) score -= scoreRun(o);
        }
    }

    return score;
}



int evaluate(const Position& pos)
{
    int score = 0;

    score += houseScore(pos);
    score += fenceScore(pos);
    score += mobilityScore(pos);
    score += destroyPotentialScore(pos);

    score += horizontalRuns(pos);
    score += verticalRuns(pos);
    score += diagonalRuns(pos);

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
    std::vector<Move> legal = pos.generateMoves();

    return legal.size();
}

int destroyPotentialScore(const Position& pos)
{
    if (pos.turn.destroy_counter < cfg::max_destroy)
        return DESTROY_POTENTIAL;
    else
        return -DESTROY_POTENTIAL;
}
