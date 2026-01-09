
#include "../gameplay/position.hpp"
#include "evaluation.hpp"

constexpr int eval_infty = 10000;

int alphabeta(Position& pos, int depth, int alpha, int beta)
{   
    int score = 0;

    std::vector<Move> legal_moves = pos.generateMoves();
    
    if (depth == 0 or legal_moves.size() == 0)
    {
        return evaluate(pos);
    }

    for (Move move : legal_moves)
    {   
        pos.makeMove(move);

        if (pos.turn.move_counter == 0)
        {
            score = -alphabeta(pos, depth - 1, -beta, -alpha);

            if (score > -beta)
                beta = score;  
        }

        else
        {
            score = alphabeta(pos, depth, alpha, beta);
        }
        
        pos.undoMove();
    }

    if (score > alpha)
        alpha = score;

    return alpha;
}

Move findBestMove(Position& pos, int depth)
{
    Move bestMove;
    int score = -eval_infty;
    std::vector<Move> legal_moves = pos.generateMoves();

    for (Move move : legal_moves)
    {   
        std::cout << "considering move " << move.square << std::endl;
        pos.makeMove(move);
        
        int move_eval;

        if (pos.turn.move_counter == 0)
        {
            move_eval = -alphabeta(pos, depth - 1, -eval_infty, eval_infty);
        }

        else
        {
            move_eval = alphabeta(pos, depth, -eval_infty, eval_infty);
        }

        if (score < move_eval)
        {
            score = move_eval;
            bestMove = move;
            std::cout << move_eval << std::endl;
        }

        pos.undoMove();    
    }

    return bestMove;
}
