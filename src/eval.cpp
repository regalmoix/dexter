#include "header.h"
#include <vector>
#include <functional>
#include <iostream>
#include <numeric>

                                    // E,  P,   N,   B,   R,   Q,    K,     p,    n,    b,    r,    q,     k   
const std::vector<S16> pieceValues    {0, 100, 290, 310, 550, 950, 10000, -100, -290, -310, -550, -950, -10000};

S16 evaluate(Board& board)
{
    return board.materialScore;
}