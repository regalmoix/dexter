#include "header.h"

#define INF     ((S16)32e3)
#define MATE    ((S16)30e3)
#define TIMEOUT ((S16)32500)

// Static Member (like a constant object) to denote Invalid Move. 
Move                    Move::Invalid_Move;
TranspositionTable      S_SEARCH::transposTable;
std::array <std::pair <Move, Move>, MAX_MOVES>   S_SEARCH::killerMoves;


S_SEARCH::S_SEARCH() :  depthMax(1), depth(1), movesTillTimeControl(0), nodesSearched(0), 
                        quit(false), stopped(false), 
                        failHigh(1), firstMoveFailHigh(0)
{
    // Fail High (Beta Cutoff) set to 1 to prevent divide by zero errors
    principalVariation.resize(25);
}


void S_SEARCH::SearchPosition(Board& board)
{
    for (std::pair <Move, Move>& killers : killerMoves)
    {
        killers.first   = Move::Invalid_Move;
        killers.second  = Move::Invalid_Move;
    }

    // Iterative Deepening
    S16 score       = 0;
    U8  currDepth   = 0;
    Move bestMove   = Move::Invalid_Move;

    for (currDepth = 1; currDepth <= depthMax; ++currDepth)
    {        
        // Else evaluate 
        S16 aspiration_alpha    = -INF;
        S16 aspiration_beta     = +INF;

        if (currDepth >= 3)
        {
            aspiration_alpha    = score - 16;
            aspiration_beta     = score + 16;
        }

        depth   = currDepth; 
        score   = AlphaBeta(board, aspiration_alpha, aspiration_beta, currDepth);

        // Evaluated outside the aspiration window so research at same depth
        if (score <= aspiration_alpha || score >= aspiration_beta)
        {
            aspiration_alpha    = -INF;
            aspiration_beta     = +INF;
            score   = AlphaBeta(board, aspiration_alpha, aspiration_beta, currDepth);
        }

        // If time over/stopped, break
        auto currTime                           = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed   = currTime - startTime;

        if (score != TIMEOUT && 1000 * elapsed.count() < timeMax)
        {   
            // Iff AB Complete, we can set depth to currDepth [Probably redundant, check later.]
            currTime    = std::chrono::high_resolution_clock::now();
            elapsed     = currTime - startTime;

            printf("\ninfo score cp %d depth %d nodes %ld time %d pv", score, depth, nodesSearched, (int)(1000*elapsed.count()));
            // printf("\ninfo score cp %d depth %d nodes %ld ord %f time %d pv", score, depth, nodesSearched, (float)firstMoveFailHigh/(float)failHigh, (int)(1000*elapsed.count()));

            auto pv = transposTable.GetPrincipalVariation(board, currDepth);
            bestMove = pv[0];
            for (Move m : pv)
            {
                if (SQLEGAL(m.fromSquare))
                {
                    printf(" ");
                    m.PrintMove();
                }
                else
                    break;
            }
        }
        else
        {
            break;
        }
        
        fflush(stdout);

        // With 30% time on the clock it is almost certain that the next iteration will not finish
        // So we refrain from using this 30% time right now.
        if (1000 * elapsed.count() > 0.7 * timeMax)
            break;
    }

    printf("\nbestmove ");
    bestMove.PrintMove();
    std::cout << std::endl;
}


S16 S_SEARCH::AlphaBeta (Board& board, S16 alpha, S16 beta, U8 currDepth)
{
    if (!(nodesSearched & 32767))
    {
        auto currTime                           = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed   = currTime - startTime;

        if (1000 * elapsed.count() > timeMax)
            return TIMEOUT;
    }

    S16     oldAlpha    = alpha;
    bool    isMate      = true;         // Stale Mate or Check Mate either counts as mate
    Move    bestMove    = Move::Invalid_Move;
    U16     legalCount  = 0;
    S16     bestScore   = -INF;

    bestMove            = transposTable.ProbeEntry(board, bestScore, alpha, beta, currDepth);

    if (bestMove != Move::Invalid_Move)
    {
        return bestScore;
    }

    if (currDepth == 0)
    {
        return Quiescence(board, alpha, beta);
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

        S16 score = -AlphaBeta(board, -beta, -alpha, currDepth - 1);

        UnmakeMove(board); 

        // Fail Hard ==> alpha <= score <= beta
        if (score == TIMEOUT)
            return TIMEOUT;

        if (score > bestScore)
        {
            bestScore   = score;
            bestMove    = move ;
            if (score >= beta)
            {
                if (legalCount == 1)
                    firstMoveFailHigh++;
                
                transposTable.StoreEntry(board, bestMove, beta, currDepth, TranspositionTable::FLAG_BETA);

                if (move.score == 0)
                {
                    killerMoves[board.plys].first    = killerMoves[board.plys].second;
                    killerMoves[board.plys].second   = move;
                }

                failHigh++;
                return beta;
            }
            
            if (score > alpha)
            {
                bestMove    = move; 
                alpha       = score;
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


S16 S_SEARCH::Quiescence (Board& board, S16 alpha, S16 beta)
{
    if (!(nodesSearched & 32767))
    {
        auto currTime                           = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed   = currTime - startTime;

        if (1000 * elapsed.count() > timeMax)
            return TIMEOUT;
    }

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
        S16 score = -Quiescence(board, -beta, -alpha);

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
            alpha       = score;
        }
    }

    return alpha;
}
