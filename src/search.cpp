#include "header.h"


#define INF     ((S16)32e3)
#define MATE    ((S16)30e3)

// Static Member (like a constant object) to denote Invalid Move. 
Move                Move::Invalid_Move;
TranspositionTable  S_SEARCH::transposTable;

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
    Move bestMove   = Move::Invalid_Move;
    startTime = std::chrono::high_resolution_clock::now();

    for (currDepth = 1; currDepth <= depthMax; ++currDepth)
    {
        score   = AlphaBeta(board, -INF, INF, currDepth/*, principalVariation[currDepth]*/);
        
        // If time over/stopped, break

        // Iff AB Complete, we can set depth to currDepth [Probably redundant, check later.]
        depth       = currDepth;
        stopTime    = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed   = stopTime - startTime;

        // bestMove    = principalVariation[currDepth][0];

        printf("\ninfo score cp %d depth %d nodes %ld time %d pv", score, depth, nodesSearched, (int)(1000*elapsed.count()));

        // for (Move m : principalVariation[currDepth])
        // {
        //     if (SQLEGAL(m.fromSquare))
        //         std::cout << " " << (char) (SQ2FILE(m.fromSquare) - 1 + 'a')  << SQ2RANK(m.fromSquare) << char(SQ2FILE(m.toSquare) - 1 + 'a' ) << SQ2RANK(m.toSquare);
        // }

        std::cout << " ||| ";
        auto pv = transposTable.GetPrincipalVariation(board, currDepth);
        bestMove = pv[0];
        for (Move m : pv)
        {
            if (SQLEGAL(m.fromSquare))
                std::cout << " " << (char) (SQ2FILE(m.fromSquare) - 1 + 'a')  << SQ2RANK(m.fromSquare) << char(SQ2FILE(m.toSquare) - 1 + 'a' ) << SQ2RANK(m.toSquare);
        }


        fflush(stdout);
    }

    char    t_prompce = ' ';

    if (bestMove.isPromotion())
    {
        switch (bestMove.getPromotedPiece())
        {
            case E_PIECE::EMPTY :   t_prompce = ' ';    break;
            case E_PIECE::bR    :   t_prompce = 'r';    break;
            case E_PIECE::wR    :   t_prompce = 'r';    break;
            case E_PIECE::bQ    :   t_prompce = 'q';    break;
            case E_PIECE::wQ    :   t_prompce = 'q';    break;
            case E_PIECE::bN    :   t_prompce = 'n';    break;
            case E_PIECE::wN    :   t_prompce = 'n';    break;
            case E_PIECE::bB    :   t_prompce = 'b';    break;
            case E_PIECE::wB    :   t_prompce = 'b';    break;
            default             :   t_prompce = ' ';    break;
        }
    }

    printf("\nbestmove ");
    std::cout   << (char)(SQ2FILE(bestMove.fromSquare) - 1 + 'a') << SQ2RANK(bestMove.fromSquare) 
                << (char)(SQ2FILE(bestMove.toSquare)   - 1 + 'a') << SQ2RANK(bestMove.toSquare) 
                << t_prompce << std::endl;
}


S16 S_SEARCH::AlphaBeta (Board& board, S16 alpha, S16 beta, U8 currDepth/*, std::vector<Move>& pv*/)
{
    // std::vector<Move> bestLine;
    
    S16     oldAlpha    = alpha;
    bool    isMate      = true;         // Stale Mate or Check Mate either counts as mate
    Move    bestMove    = Move::Invalid_Move;
    U16     legalCount  = 0;
    S16     bestScore   = -INF;

    bestMove            = transposTable.ProbeEntry(board, bestScore, alpha, beta, currDepth);

    if (bestMove != Move::Invalid_Move)
    {
        // pv.push_back(bestMove);
        return bestScore;
    }

    if (currDepth == 0)
    {
        // pv.clear();
        return Quiescence(board, alpha, beta/*, pv*/);
    }

    // All Nodes visited by Search includes A-B + Quiescence 
    nodesSearched++;

    std::vector<Move> moveList;
    AllMoves  (board, moveList);
    std::sort (moveList.begin(), moveList.end(), std::greater<Move>());

    bestScore   = -INF;
    for (Move& move : moveList)
    {
        if (!MakeMove(board, move))  
            continue;

        isMate = false;
        legalCount++;

        // bestLine.clear();
        S16 score = -AlphaBeta(board, -beta, -alpha, currDepth - 1/*, bestLine*/);

        UnmakeMove(board); 

        // Fail Hard ==> alpha <= score <= beta

        if (score > bestScore)
        {
            bestScore   = score;
            bestMove    = move ;
            if (score >= beta)
            {
                if (legalCount == 1)
                    firstMoveFailHigh++;
                
                transposTable.StoreEntry(board, bestMove, beta, currDepth, TranspositionTable::FLAG_BETA);

                failHigh++;
                return beta;
            }
            
            if (score > alpha)
            {
                bestMove    = move; 
                alpha       = score;

                // pv.clear();
                // pv.push_back(move);
                // pv.insert(std::end(pv), std::begin(bestLine), std::end(bestLine));
            }
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
            return -(MATE) - currDepth;
        }

        else
            return 0;
    }


    if (alpha != oldAlpha)
    {
        transposTable.StoreEntry(board, bestMove, bestScore, currDepth, TranspositionTable::FLAG_EXACT);
    }
    else
    {
        transposTable.StoreEntry(board, bestMove, alpha, currDepth, TranspositionTable::FLAG_ALPHA);
    }

    return alpha;
}


S16 S_SEARCH::Quiescence (Board& board, S16 alpha, S16 beta/*, std::vector<Move>& pv*/)
{
    // std::vector<Move> bestLine;

    nodesSearched++;

    auto eval = evaluate(board);

    if (eval >= beta)
        return beta;

    if (eval > alpha)
        alpha = eval;

    std::vector<Move> moveList;

    #define CAP_MOVES_ONLY 1

    AllMoves(board, moveList, CAP_MOVES_ONLY);


    std::sort(moveList.begin(), moveList.end(), std::greater<Move>());

    U16 legalCount = 0;
    for (Move& move : moveList)
    {
        if (!MakeMove(board, move))  
            continue;

        legalCount++;

        // bestLine.clear();
        S16 score = -Quiescence(board, -beta, -alpha/*, bestLine*/);

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
            // pv.clear();
            // pv.push_back(move);
            // pv.insert(std::end(pv), std::begin(bestLine), std::end(bestLine));
 
            alpha       = score;
        }
    }

    return alpha;
}
