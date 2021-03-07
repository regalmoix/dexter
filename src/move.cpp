#include "header.h"

/** NOTE
 *  
 *  Bit representation format of moveKind.
 *  
 *  isCheck : 1; 
 *  enPassant : 1;
 *  doublePush : 1;
 *  castle : 2;
 *  promotion : 1
 *  promoted piece : 2;
 * 
 *  CHK | EP | DP | CA | CA | P | PP | PP
 *  
 *  ((CHK) << 7 | (EP) << 6 | (DP) << 5 | (CA) << 3 | (P) << 2 | (PP))
**/

bool S_MOVE::isNormalCapture()
{
    return (((pieceInfo & 0xF0) >> 4) != E_PIECE::EMPTY);
}


bool S_MOVE::isEPCapture()
{
    return (moveData >> 6) & 1;
}


bool S_MOVE::isCheck()
{
    return (moveData >> 7) & 1;
}


bool S_MOVE::isPawnDoublePush()
{
    return (moveData >> 5) & 1;
}


bool S_MOVE::isPromotion()
{
    return (moveData >> 2) & 1;
}


E_PIECE S_MOVE::getPromotedPiece()
{
    if (!isPromotion())
        return E_PIECE::EMPTY;

    U8 PromotedPiece = moveData & 0x3;                      // Last 2 bits are Prom Piece

    U8 sideToMove = PIECECOLOR(getMovingPiece());           // WHITE = 0 and BLACK = 1

    return static_cast<E_PIECE>((sideToMove * 6) + PromotedPiece + 2);
}


void S_MOVE::setAttributes (U8 moveInfo)
{
    // Simply PACKMOVE all attributes to make moveInfo and here we bitwise OR with existing moveData to set those attributes
    moveData        |= moveInfo; 
}


void S_MOVE::unsetAttributes (U8 moveInfo)
{
    // Simply PACKMOVE all attributes to make moveInfo and here we bitwise AND the complement moveInfo with existing moveData to unset those attributes
    moveData        &= (~moveInfo); 
}


U8 S_MOVE::getMovingPiece()
{
    return pieceInfo & 0x0F;
}


U8 S_MOVE::getCapturedPiece()
{
    return (pieceInfo & 0xF0) >> 4;
}


S_MOVE::S_MOVE(Board board, U8 from, U8 to)                 // Assume Non Special Move
{
    fromSquare      = from;
    toSquare        = to;

    // Verify that Move is made when Board is in consistent state. Else we will set wrong Pieces when Getting Piece on Square.
    U8 t_currPiece  = board.GetPieceOnSquare(from);
    U8 t_capPiece   = board.GetPieceOnSquare(to);                                      

    assert (!(t_currPiece == E_PIECE::wP && SQ2RANK(to) == E_RANK::Rank_8));                        
    assert (!(t_currPiece == E_PIECE::bP && SQ2RANK(to) == E_RANK::Rank_1));                        

    pieceInfo       = 0;
    pieceInfo       |= t_capPiece << 4;
    pieceInfo       |= t_currPiece;

    U8 t_check      = 0;
    U8 t_isProm     = 0;
    U8 t_promPce    = E_PIECE::EMPTY;
    U8 t_pawnFirst  = 0;
    U8 t_castle     = 0;
    U8 t_EP         = 0;

    moveData        = PACKMOVE(t_check, t_EP, t_pawnFirst, t_castle, t_isProm, t_promPce);
}


S_MOVE::S_MOVE (Board board, U8 from, U8 to, U8 moveInfo)
{
    fromSquare      = from;
    toSquare        = to;
    
    moveData        = moveInfo;

    U8 t_currPiece  = board.GetPieceOnSquare(from);
    U8 t_capPiece   = E_PIECE::EMPTY;
    
    if (!isEPCapture())
        t_capPiece = board.GetPieceOnSquare(to);
    
    else
    {
        // NOTE that EP Square has FILE = FILE of TO sq and RANK = RANK of FROM sq

        U8 t_epSq   = FR2SQ (SQ2FILE(toSquare), SQ2RANK(fromSquare));

        t_capPiece  = board.GetPieceOnSquare(t_epSq);
    }
        
    pieceInfo       = 0;
    pieceInfo       |= t_capPiece << 4;
    pieceInfo       |= t_currPiece;
}


S_MOVE::S_MOVE (Board board, U8 from, U8 to, U8 moveInfo, U8 pieceInfo)
{
    fromSquare              = from;
    toSquare                = to;
    
    this->moveData          = moveInfo;        
    this->pieceInfo         = pieceInfo;
}
