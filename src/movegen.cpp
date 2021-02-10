#include "header.h"

std::vector<S_MOVE> moveList;

void addQuietMove(Board& board, Move& move)       // Here means No Capture
{
    moveList.push_back(move);
}


void addCaptureMove(Board& board, Move& move)        // Here means No Capture
{
    moveList.push_back(move);
}


void PawnMoves(Board& board)
{
    if (board.GetSideToMove() == E_COLOR::WHITE)
    {
        auto pawnSqList = board.GetSquareList(E_PIECE::wP);

        for (U8 pawnSquare : pawnSqList)
        {
            assert (pawnSquare != E_SQUARE::Square_Invalid);
            assert (SQ2RANK(pawnSquare) != E_RANK::Rank_8);

            if (SQ2RANK(pawnSquare) == E_RANK::Rank_7)  // These can not be quiet moves
            {
                // Rank 7 -> 8 Quiet Promotion
                if (board.GetPieceOnSquare(pawnSquare + 10) == E_PIECE::EMPTY)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 10, PACKMOVE(0, 0, 0, 0, 1, x));
                        addQuietMove(board, move);
                    }           
                }


                // Rank 7 -> 8 Capture Promotions
                if (SQLEGAL(pawnSquare + 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 9)) == E_COLOR::BLACK)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 9, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(board, move);
                    } 
                }

                if (SQLEGAL(pawnSquare + 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 11)) == E_COLOR::BLACK)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 11, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(board, move);
                    } 
                }
                continue;
            }

            // Pawn not on Ranks 7 or 8, Quiet Move
            if (board.GetPieceOnSquare(pawnSquare + 10) == E_PIECE::EMPTY)
            {
                Move move(board, pawnSquare, pawnSquare + 10);
                addQuietMove(board, move);
            }

            // Pawn not on Ranks 7 or 8, Double Push Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_2) && (board.GetPieceOnSquare(pawnSquare + 20) == E_PIECE::EMPTY))
            {
                Move move(board, pawnSquare, pawnSquare + 20, PACKMOVE(0,0,1,0,0,0));
                addQuietMove(board, move);
            }

            // Pawn not on Ranks 7 or 8, Capture Moves
            if (SQLEGAL(pawnSquare + 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 9)) == E_COLOR::BLACK)
            {
                    Move move(board, pawnSquare, pawnSquare + 9);
                    addCaptureMove(board, move); 
            }

            if (SQLEGAL(pawnSquare + 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 11)) == E_COLOR::BLACK)
            {
                Move move(board, pawnSquare, pawnSquare + 11);
                addCaptureMove(board, move);  
            }


            // Pawn on Rank 5, En Passant Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_5) && SQLEGAL(pawnSquare + 9) && (board.GetEPSquare() == pawnSquare + 9))
            {
                Move move(board, pawnSquare, pawnSquare + 9, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(board, move);
            }

            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_5) && SQLEGAL(pawnSquare + 11) && (board.GetEPSquare() == pawnSquare + 11))
            {
                Move move(board, pawnSquare, pawnSquare + 11, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(board, move);
            }
        }
    }

    else if (board.GetSideToMove() == E_COLOR::BLACK)
    {
        // everything above but - instead of +, I suppose.
    }
}