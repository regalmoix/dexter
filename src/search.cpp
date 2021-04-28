#include "header.h"


#define INF     ((S16)3e4)
#define MATE    ((S16)32e3)

void S_SEARCH::Search_f(Board& board)
{
    // Iterative Deepening
    S16 score       = 0;
    U8  currDepth   = 0;

    for (currDepth = 1; currDepth <= depthMax; ++currDepth)
    {
        cout << "Curr depth : " << (int)currDepth << endl;
        score   = AlphaBeta(board, -INF, INF, currDepth);
        
        // If time over/stopped, break

        // Iff AB Complete, we can set depth to currDepth [Probably redundant, check later.]
        depth   = currDepth;
        std::cout << "Score : " << (int)score << std::endl;
    }

}


S16 S_SEARCH::AlphaBeta (Board& board, S16 alpha, S16 beta, U8 currDepth)
{
    bool isMate     = true;         // Stale Mate or Check Mate either counts as mate
    Move bestMove (board, E_SQUARE::Square_Invalid, E_SQUARE::Square_Invalid);

    if (currDepth == 0)
    {
        return Quiescence(board, alpha, beta);
    }

    std::vector<Move> moveList;
    AllMoves(board, moveList);

    for (Move move : moveList)
    {
        if (!MakeMove(board, move))  
            continue;

        isMate = false;

        S16 score = -AlphaBeta(board, -beta, -alpha, currDepth - 1);

        UnmakeMove(board); 

        // Fail Hard ==> alpha <= score <= beta

        if (score >= beta)
            return beta;
        
        if (score > alpha)
        {
            bestMove    = move; 
            alpha       = score;
        }
    }


    if (isMate)
    {
        // cout << "Mate" << endl;

        U8 king                     = ((board.GetSideToMove() == E_COLOR::WHITE) ? E_PIECE::wK : E_PIECE::bK);
        U8 kingSq                   = E_SQUARE::Square_Invalid;
        std::vector<U8> kingList    = board.GetSquareList(king);

        for (U8 sq : kingList)
        {
            if (SQLEGAL(sq))
            {
                kingSq = sq;
                break;
            }
        }
        
        // cout << "King Sq" << (int)kingSq << endl;
        
        if (isAttacked(board, kingSq))
        {
            // cout  << "Check Mate";
            return -MATE;
        }

        else
            return 0;
    }

    return alpha;
}


S16 S_SEARCH::Quiescence (Board& board, S16 alpha, S16 beta)
{
    this->nodesSearched ++;
    this->nodesSearched += alpha - alpha + beta - beta;
    return evaluate(board);
}
