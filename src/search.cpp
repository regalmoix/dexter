#include "header.h"


#define INF     ((S16)3e4)
#define MATE    ((S16)32e3)

void S_SEARCH::SearchPosition(Board& board)
{
    // Iterative Deepening
    S16 score       = 0;
    U8  currDepth   = 0;

    for (currDepth = 1; currDepth <= depthMax; ++currDepth)
    {
        cout << "Curr depth : " << (int)currDepth;
        score   = AlphaBeta(board, -INF, INF, currDepth, principalVariation[depth]);
        
        // If time over/stopped, break

        // Iff AB Complete, we can set depth to currDepth [Probably redundant, check later.]
        depth   = currDepth;
        std::cout << "\tScore : " << (int)score << "\tNodes : " << (int) nodesSearched << "\t";

        for (Move m : principalVariation[depth - 1])
        {
            if (SQLEGAL(m.fromSquare))
                std::cout << (char) (SQ2FILE(m.fromSquare) - 1 + 'A')  << SQ2RANK(m.fromSquare) << "->" << char(SQ2FILE(m.toSquare) - 1 + 'A' ) << SQ2RANK(m.toSquare) << " ";
        }

        cout << endl;
    }

}


S16 S_SEARCH::AlphaBeta (Board& board, S16 alpha, S16 beta, U8 currDepth, std::vector<Move>& pv)
{
    // S16 ogAlpha = alpha;

    std::vector<Move> bestLine;

    bool isMate     = true;         // Stale Mate or Check Mate either counts as mate
    Move bestMove (board, E_SQUARE::Square_Invalid, E_SQUARE::Square_Invalid);

    if (currDepth == 0)
    {
        pv.clear();
        return Quiescence(board, alpha, beta);
    }

    std::vector<Move> moveList;
    AllMoves(board, moveList);

    for (Move move : moveList)
    {
        if (!MakeMove(board, move))  
            continue;

        isMate = false;

        bestLine.clear();
        S16 score = -1 * AlphaBeta(board, -1*beta, -1*alpha, currDepth - 1, bestLine);

        UnmakeMove(board); 

        // Fail Hard ==> alpha <= score <= beta

        if (score >= beta)
        {
            return beta;
        }
        
        if (score > alpha)
        {
            bestMove    = move; 
            alpha       = score;

            pv.clear();
            pv.push_back(move);
            pv.insert(std::end(pv), std::begin(bestLine), std::end(bestLine));
    
        }
    }


    if (isMate)
    {
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
                
        if (isAttacked(board, kingSq))
        {
            return -MATE;
        }

        else
            return 0;
    }

    // if (alpha != ogAlpha)
    // {
    //         principalVariation[currDepth].clear();
    //         principalVariation[depth].push_back(bestMove);
    //         principalVariation[depth].insert(std::end(principalVariation[depth]), std::begin(bestLine), std::end(bestLine));
    // }

    return alpha;
}


S16 S_SEARCH::Quiescence (Board& board, S16 alpha, S16 beta)
{
    this->nodesSearched ++;
    this->nodesSearched += alpha - alpha + beta - beta;
    return evaluate(board);
}
