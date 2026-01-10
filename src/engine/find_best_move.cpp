
#include "../gameplay/position.hpp"
#include "evaluation.hpp"

constexpr int eval_infty = 1000000;
constexpr int win_eval = eval_infty/10;
constexpr int depth_eval = eval_infty/100;

int nodes_searched = 0;
int nodes_pruned = 0;

int alphabeta(Position& pos, int depth, int alpha, int beta)
{   
    if (pos.turn.current == playerWin(pos))
    {
        return win_eval + depth_eval*depth;
    }

    if (pos.turn.other == playerWin(pos))
    {
        return -(win_eval + depth_eval*depth);
    }

    int score = 0;

    if (depth == 0)
    {   
        return evaluate(pos);
    }

    std::vector<Move> legal_moves = pos.generateMoves();

    if (legal_moves.size() == 0)
    {   
        std::cout << "no legal moves at depth " << depth << std::endl;
        return evaluate(pos);
    }

    for (const Move& move : legal_moves)
    {   
        nodes_searched++;

        pos.makeMove(move);

        if (pos.turn.move_counter == 0)
        {
            score = -alphabeta(pos, depth - 1, -beta, -alpha);
        }

        else
        {
            score = alphabeta(pos, depth - 1, alpha, beta);
        }
        
        pos.undoMove();

        if (score > alpha)
            alpha = score;

        if (alpha > beta - 1)
        {
            nodes_pruned += (int)legal_moves.size() - 1; // siblings skipped            
            break;   
        }
    }

    return alpha;
}

Move findBestMove(Position& pos, int depth)
{   
    Move bestMove;
    int score = -eval_infty;
    std::vector<Move> legal_moves = pos.generateMoves();

    for (const Move& move : legal_moves)
    {   
        pos.makeMove(move);
        
        int move_eval;

        if (pos.turn.move_counter == 0)
        {
            move_eval = -alphabeta(pos, depth - 1, -eval_infty, eval_infty);
        }
        else
        {
            move_eval = alphabeta(pos, depth - 1, -eval_infty, eval_infty);
        }

        if (move_eval > score)
        {
            score = move_eval;
            bestMove = move;
        }

        pos.undoMove();  
        
        if (score > win_eval)
        {
            return bestMove;
        }
    }

    return bestMove;
    
}


