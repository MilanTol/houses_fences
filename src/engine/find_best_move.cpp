
#include "../gameplay/position.hpp"
#include "evaluation.hpp"

constexpr int min_eval = -10000;

int negamax(Position& pos, int depth, int alpha, int beta, int movesMadeThisTurn = 0)
{
    if (depth == 0)
        return evaluate(pos);

    std::vector<Move> moves = pos.generateMoves();

    if (moves.empty())
        return evaluate(pos);

    for (const Move& m : moves)
    {
        pos.makeMove(m);

        int score;
        if (movesMadeThisTurn + 1 < 2)
        {
            // Not finished turn yet, same player continues
            score = negamax(pos, depth, alpha, beta, movesMadeThisTurn + 1);
        }
        else
        {
            // Finished turn, switch player and decrease depth
            score = -negamax(pos, depth - 1, -beta, -alpha, 0);
        }

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
    int bestScore = min_eval;

    std::vector<Move> moves = pos.generateMoves();

    for (const Move& m : moves)
    {
        pos.makeMove(m);
        int score = -negamax(pos, depth - 1, min_eval, -min_eval);
        pos.undoMove();

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = m;
        }
    }

    return bestMove;
}
