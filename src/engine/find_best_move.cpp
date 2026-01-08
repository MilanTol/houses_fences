
#include "../gameplay/position.hpp"
#include "evaluation.hpp"

int negamax(Position& pos, int depth, int alpha, int beta)
{
    if (depth == 0)
        return evaluate(pos);

    auto moves = pos.generateMoves();

    if (moves.empty())
        return evaluate(pos);

    for (const Move& m : moves)
    {
        pos.makeMove(m);
        int score = -negamax(pos, depth - 1, -beta, -alpha);
        pos.undoMove();

        if (score >= beta)
            return beta;

        alpha = std::max(alpha, score);
    }

    return alpha;
}

Move findBestMove(Position& pos, int depth)
{
    Move bestMove{};
    int bestScore = -1000000;

    auto moves = pos.generateMoves();

    for (const Move& m : moves)
    {
        pos.makeMove(m);
        int score = -negamax(pos, depth - 1, -1000000, 1000000);
        pos.undoMove();

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = m;
        }
    }

    return bestMove;
}
