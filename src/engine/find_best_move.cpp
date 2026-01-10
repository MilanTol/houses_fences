
#include "../gameplay/position.hpp"
#include "evaluation.hpp"

constexpr int eval_infty = 100000;

int nodes_searched = 0;
int nodes_pruned = 0;

int alphabeta(Position& pos, int depth, int alpha, int beta)
{   
    if (pos.turn.current == playerWin(pos))
    {
        return (eval_infty - 1);
    }

    if (pos.turn.other == playerWin(pos))
    {
        return -(eval_infty - 1);
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
    nodes_pruned = 0;
    nodes_searched = 0;

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

        if (score < move_eval)
        {
            score = move_eval;
            bestMove = move;
        }

        pos.undoMove();    
    }

    std::cout << "Nodes searched: " << nodes_searched << std::endl;
    std::cout << "Nodes pruned:   " << nodes_pruned << std::endl;

    double ratio = (double)nodes_pruned / (nodes_searched + nodes_pruned);
    std::cout << "Pruning ratio:  " << ratio << std::endl;

    return bestMove;
    
}


