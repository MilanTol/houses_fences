# pragma once

#include "../gameplay/position.hpp"
#include "evaluation.hpp"

Move findBestMove(Position& pos, int depth);
int negamax(Position& pos, int depth, int alpha, int beta);