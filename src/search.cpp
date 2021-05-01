#include "header.h"


#define INF     ((S16)32e3)
#define MATE    ((S16)30e3)

// Static Member (like a constant object) to denote Invalid Move. 
Move Move::Invalid_Move;


S_SEARCH::S_SEARCH() :  depthMax(1), depth(1), movesTillTimeControl(0), nodesSearched(0), 
                        quit(false), stopped(false), 
                        failHigh(1), firstMoveFailHigh(0)
{
    // Fail High (Beta Cutoff) set to 1 to prevent divide by zero errors
    principalVariation.resize(25);
}


void S_SEARCH::SearchPosition(Board& board)
{
    // Iterative Deepening
    S16 score       = 0;
    U8  currDepth   = 0;

    startTime = std::chrono::high_resolution_clock::now();


    printf("D  |   Score   |    Speed    |   Ord %%   |\tPV\n");
    printf("---|-----------|-------------|-----------|-----------------------------------------\n");

    for (currDepth = 1; currDepth <= depthMax; ++currDepth)
    {
        score   = AlphaBeta(board, -INF, INF, currDepth, principalVariation[currDepth]);
        
        // If time over/stopped, break

        // Iff AB Complete, we can set depth to currDepth [Probably redundant, check later.]
        depth       = currDepth;
        stopTime    = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed   = stopTime - startTime;
        U16 speed   = nodesSearched/(1000*elapsed.count());

        printf("%-2d |  %7.2f  | %6dKN/s  |   %5.2f   | ", depth, (float)score/100, speed, 100*(float)firstMoveFailHigh/(float)failHigh);

        for (Move m : principalVariation[currDepth])
        {
            std::cout << (char) (SQ2FILE(m.fromSquare) - 1 + 'A')  << SQ2RANK(m.fromSquare) << "->" << char(SQ2FILE(m.toSquare) - 1 + 'A' ) << SQ2RANK(m.toSquare) << " ";
        }

        cout << endl;

    }
}


S16 S_SEARCH::AlphaBeta (Board& board, S16 alpha, S16 beta, U8 currDepth, std::vector<Move>& pv)
{
    std::vector<Move> bestLine;
    
    bool isMate     = true;         // Stale Mate or Check Mate either counts as mate
    Move bestMove (board, E_SQUARE::Square_Invalid, E_SQUARE::Square_Invalid);

    if (currDepth == 0)
    {
        pv.clear();
        return Quiescence(board, alpha, beta);
    }

    // All Nodes visited by Search includes A-B + Quiescence 
    nodesSearched++;

    std::vector<Move> moveList;
    AllMoves(board, moveList);

    std::stable_sort(moveList.rbegin(), moveList.rend());


    U16 legalCount = 0;
    for (Move move : moveList)
    {
        
        if (!MakeMove(board, move))  
            continue;

        isMate = false;
        legalCount++;

        bestLine.clear();
        S16 score = -AlphaBeta(board, -beta, -alpha, currDepth - 1, bestLine);

        UnmakeMove(board); 

        // Fail Hard ==> alpha <= score <= beta

        if (score >= beta)
        {
            if (legalCount == 1)
                firstMoveFailHigh++;
            
            failHigh++;
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
            return -(MATE);
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
