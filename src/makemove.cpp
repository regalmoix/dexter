#include "header.h"

S_HASH HASH;

#define HASHPIECE(board, pce, sq120)      (board.posHashKey ^= HASH.pieceSquarePairHash[pce][sq120])   
#define HASHCASTLE(board, castlePerm)     (board.posHashKey ^= HASH.castleHash[castlePerm])
#define HASHEP(board, epSq)               (board.posHashKey ^= HASH.epHash[SQ2FILE(epSq)])
#define HASHSIDE(board, side)             (board.posHashKey ^= (HASH.sideToMoveHash & side))

#define UNHASHPIECE(board, pce, sq120)    (board.posHashKey ^= HASH.pieceSquarePairHash[pce][sq120])   
#define UNHASHCASTLE(board, castlePerm)   (board.posHashKey ^= HASH.castleHash[castlePerm])
#define UNHASHEP(board, epSq)             (board.posHashKey ^= HASH.epHash[SQ2FILE(epSq)])
#define UNHASHSIDE(board, side)           (board.posHashKey ^= (HASH.sideToMoveHash & side))


void RemovePiece(Board& board, U8 pce, U8 sq120)
{
    assert(board.GetPieceOnSquare(sq120) == pce);

    board.ModifySquareList(pce, sq120, "del");
    board.SetPieceOnSquare(sq120, E_PIECE::EMPTY);

    UNHASHPIECE(board, pce, sq120);


    // If Pawn pce, check EP
    // If King check castle.
    
}