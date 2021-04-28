#include "header.h"

S_HASH HASH;

const int CastlePerm[120] = 
{
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

#define HASHPIECE(board, pce, sq120)        (board.posHashKey ^= HASH.pieceSquarePairHash[pce][sq120])   
#define HASHCASTLE(board, castlePerm)       (board.posHashKey ^= HASH.castleHash[castlePerm])
#define HASHEP(board, epSq)                 (board.posHashKey ^= HASH.epHash[SQ2FILE(epSq)])
#define HASHSIDE(board, side)               (board.posHashKey ^= ((side == 1) ? HASH.sideToMoveHash : 0))

#define UNHASHPIECE(board, pce, sq120)      (board.posHashKey ^= HASH.pieceSquarePairHash[pce][sq120])   
#define UNHASHCASTLE(board, castlePerm)     (board.posHashKey ^= HASH.castleHash[castlePerm])
#define UNHASHEP(board, epSq)               (board.posHashKey ^= HASH.epHash[SQ2FILE(epSq)])
#define UNHASHSIDE(board, side)             (board.posHashKey ^= ((side == 1) ? HASH.sideToMoveHash : 0))


/** Removes a piece from Piecelist, Board and Updates Count
 *  
 *  @param  board   The current position
 *  @param  sq120   The square to remove piece on
 * 
 *  @return         Removed piece (passed explicitly as a parameter / gets piece on square)  
 * 
**/
static U8 RemovePiece (Board& board, U8 sq120)
{    
    U8 pce = board.GetPieceOnSquare(sq120);
    assert (SQLEGAL(sq120));
    assert (pce != E_PIECE::OFFBOARD);
    assert (pce != E_PIECE::EMPTY);

    board.ModifySquareList(pce, sq120, "del");
    board.SetPieceOnSquare(sq120, E_PIECE::EMPTY);

    UNHASHPIECE(board, pce, sq120);

    // board.countPiece[pce]--;  

    board.materialScore -= pieceValues[pce];    // CHECK THIS

    return pce;
}


/** Adds a piece to Piecelist, Board and Updates Count
 *  
 *  @param  board   The current position
 *  @param  sq120   The square to put piece on
 *  @param  pce     The piece to be add.
 * 
 *  @return         The captured piece  
 * 
**/
static U8 AddPiece (Board& board, U8 sq120, U8 pce)
{   
    assert(SQLEGAL(sq120));

    board.ModifySquareList(pce, sq120, "add");
    U8 capPiece = board.SetPieceOnSquare(sq120, static_cast<E_PIECE>(pce));

    assert(pce != E_PIECE::EMPTY);
    assert(pce != E_PIECE::OFFBOARD);

    HASHPIECE(board, pce, sq120);

    // board.countPiece[pce]++;
    board.materialScore += pieceValues[pce];    // CHECK THIS

   
    return capPiece;
}


/** Move a Piece from the from square to the to square
 *  
 *  @param  board   The current position
 *  @param  from    The square the piece is on
 *  @param  to      The square the piece goes to
 * 
 *  @return         The captured piece 
 * 
**/
static U8 MovePiece (Board& board, U8 from, U8 to)
{
    assert(SQLEGAL(from));
    assert(SQLEGAL(to));
    
    U8 pce      = RemovePiece (board, from);
    U8 capPce   = AddPiece (board, to, pce);

    return capPce;
}


/** Makes a move (if legal) and updates Board Data Structure accordingly.
 *  
 *  @param  board   The current position
 *  @param  move    The pseudo-legal move to make
 * 
 *  @return true iff the move is legal and succesfully made, false if King is in check after move made.
**/ 
bool MakeMove (Board& board, Move move)
{
    assert(sizeof(board) != 0);
    assert(sizeof(move) != 0);

    
    U8 from     = move.fromSquare;
    U8 to       = move.toSquare;
    U8 side     = board.GetSideToMove();
    U8 epSq     = board.GetEPSquare();
    U8 castPerm = board.GetCastleRights();
    U8 cnt50    = board.fiftyMoveRuleCount;


    assert(SQLEGAL(from));
    assert(SQLEGAL(to));


    History histData(move, board.posHashKey, epSq, castPerm, cnt50);
    assert(sizeof(histData) != 0);
    board.moveHistory.push_back(histData);

    // Unhash current position parameters and later hash in their updated values
    // if (SQLEGAL(epSq))
    UNHASHEP(board, epSq);
    UNHASHCASTLE(board, castPerm);
    UNHASHSIDE  (board, side);

    // Set EP Square to Invalid. If double push, we handle it later
    board.enPassantSquare = E_SQUARE::Square_Invalid;

    // If EP then remove the captured piece
    if (move.isEPCapture())
    {
        if (side == E_COLOR::WHITE)
        {
            assert (board.GetPieceOnSquare(to - 10) == move.getCapturedPiece());
            RemovePiece(board, to - 10);
        }

        else if (side == E_COLOR::BLACK)
        {
            assert (board.GetPieceOnSquare(to + 10) == move.getCapturedPiece());
            RemovePiece(board, to + 10);
        }
    }

    // If Castle Move Rook since this is only move where 2 pieces move together.
    switch(move.getCastle())
    {
        // No Castle
        case 0 : break;

        // Invalid. Should never be this
        case 1 : break;

        // KingSide Castle
        case 2 :
        {
            if (to == E_SQUARE::G1)
            {
                assert (side == E_COLOR::WHITE);
                MovePiece (board, E_SQUARE::H1, E_SQUARE::F1);
            }

            else if (to == E_SQUARE::G8)
            {
                assert (side == E_COLOR::BLACK);
                MovePiece (board, E_SQUARE::H8, E_SQUARE::F8);
            }

            else
                assert (false);

            break;
        }

        // QueenSide Castle
        case 3 :
        {
            if (to == E_SQUARE::C1)
            {
                assert (side == E_COLOR::WHITE);
                MovePiece (board, E_SQUARE::A1, E_SQUARE::D1);
            }

            else if (to == E_SQUARE::C8)
            {
                assert (side == E_COLOR::BLACK);
                MovePiece (board, E_SQUARE::A8, E_SQUARE::D8);                
            }

            else
                assert (false);
            
            break;
        } 
    }
    
    // If DoublePush, Set new EP square
    if (move.isPawnDoublePush())
    {
        if (side == E_COLOR::WHITE)
        {
            board.enPassantSquare = to - 10;
            assert (SQ2RANK(to - 10) == E_RANK::Rank_3);
            // HASHEP(board, to - 10);
        }

        else if (side == E_COLOR::BLACK)
        {
            board.enPassantSquare = to + 10;
            assert (SQ2RANK(to + 10) == E_RANK::Rank_6);
            // HASHEP(board, to + 10);
        }
    }


    // If Capture remove captured piece. (reset 50cnt also)
    if (move.getCapturedPiece() != E_PIECE::EMPTY)
    {
        // En Passant captures have already been handled previously
        if (move.isCapture() && !move.isEPCapture())
        {
            RemovePiece(board, to);
        }
        board.fiftyMoveRuleCount = 0;     
    }

    else if (move.getMovingPiece() == E_PIECE::wP || move.getMovingPiece() == E_PIECE::bP) 
        board.fiftyMoveRuleCount = 0; 

    else 
        board.fiftyMoveRuleCount ++;

    // Move the piece
    MovePiece(board, from, to);

    assert(SQLEGAL(from));
    assert(SQLEGAL(to));

    // If Promotion, remove the pawn add the promoted piece
    if (move.isPromotion())
    {
        // Remove the pawn on rank 8 or 1  
        assert (move.getMovingPiece() == E_PIECE::wP || move.getMovingPiece() == E_PIECE::bP);
        assert (SQ2RANK(to) == E_RANK::Rank_1 || SQ2RANK(to) == E_RANK::Rank_8); 
        RemovePiece(board, to);
        
        // Add the promotion Piece
        AddPiece(board, to, move.getPromotedPiece());
    }

    board.castleRights &= CastlePerm[from];
    board.castleRights &= CastlePerm[to];
    HASHCASTLE(board, board.castleRights);

    // Switch side, increment ply count
    board.sideToMove ^= 1;
    board.plys ++;
    HASHSIDE(board, board.GetSideToMove());

    // Re Hash new EP Square (irrespective of legal or not)
    HASHEP(board, board.GetEPSquare());

    U8 wkingSq = E_SQUARE::Square_Invalid;
    U8 bkingSq = E_SQUARE::Square_Invalid;

    for  (U8 x : board.GetSquareList(E_PIECE::wK))
    {
        if (SQLEGAL(x))
        {
            wkingSq =  x;
            break;
        }
    }

    for  (U8 x : board.GetSquareList(E_PIECE::bK))
    {
        if (SQLEGAL(x))
        {
            bkingSq =  x;
            break;
        }
    }

    assert(SQLEGAL(wkingSq));
    assert(SQLEGAL(bkingSq));
    
    // Check King in check at last
    if (side == E_COLOR::WHITE)
    {

        if (isAttacked(board, wkingSq, E_COLOR::BLACK))
        {
            UnmakeMove(board);
            return false;
        }
    }

    else if (side == E_COLOR::BLACK)
    {
        if (isAttacked(board, bkingSq, E_COLOR::WHITE))
        {
            UnmakeMove(board);
            return false;
        }
    }

    assert (board.posHashKey == HASH.GenerateHash(board));
    
    return true;
}


/** Undo the last move made and restore the Board Data Structure appropriately.
 *  
 *  @param  board   The current position
 * 
 *  @return None
**/ 
void UnmakeMove (Board& board)
{
    board.plys --;
    History histData = board.moveHistory.back();
    board.moveHistory.pop_back();

    Move move   = histData.move;
    U8 from     = move.fromSquare;
    U8 to       = move.toSquare;

    // if (SQLEGAL(board.enPassantSquare))
    UNHASHEP(board, board.enPassantSquare);
    UNHASHCASTLE(board, board.GetCastleRights());
    UNHASHSIDE(board, board.GetSideToMove());

    // Restore the data fields from history and flip back the side to move
    board.castleRights          = histData.castlePermissions;
    board.fiftyMoveRuleCount    = histData.fiftyCount;
    board.enPassantSquare       = histData.enPassantSquare;
    board.sideToMove            ^= 1;
    // board.posHashKey            = histData.posHashKey;   // Possible to directly use the stored Hash Key instead of unhashing like we do now.

    // if (SQLEGAL(board.enPassantSquare))
    HASHEP(board, board.enPassantSquare);
    HASHCASTLE(board, board.GetCastleRights());
    HASHSIDE(board, board.GetSideToMove());


    if (move.isEPCapture())
    {
        if (board.sideToMove == E_COLOR::WHITE)
        {
            AddPiece(board, to - 10, E_PIECE::bP);
        }

        else if (board.sideToMove == E_COLOR::BLACK)
        {
            AddPiece(board, to + 10, E_PIECE::wP);
        }
    }

    switch(move.getCastle())
    {
        // No Castle
        case 0 : break;

        // Invalid. Should never be this
        case 1 : break;

        // KingSide Castle
        case 2 :
        {
            if (to == E_SQUARE::G1)
                MovePiece (board, E_SQUARE::F1, E_SQUARE::H1);            

            else if (to == E_SQUARE::G8)
                MovePiece (board, E_SQUARE::F8, E_SQUARE::H8);            

            else
            {
                assert (false);
            }

            break;
        }

        // QueenSide Castle
        case 3 :
        {
            if (to == E_SQUARE::C1)
                MovePiece (board, E_SQUARE::D1, E_SQUARE::A1);

            else if (to == E_SQUARE::C8)
                MovePiece (board, E_SQUARE::D8, E_SQUARE::A8);                

            else
                assert (false);
            
            break;
        } 
    }
    
    // Move Back the piece from the 'to' square to the 'from' square.
    MovePiece(board, to, from);

    
    // For normal captures we undo by putting the captured piece back on the 'to' square
    if (move.isCapture() && !move.isEPCapture())
    {
        AddPiece(board, to, move.getCapturedPiece());
    }
    
    if (move.isPromotion())
    {
        // MovePiece above move the promoted piece to the 'from' square so we clear the from square and update it with Pawn
        RemovePiece(board, from);
        AddPiece(board, from, (board.GetSideToMove() == E_COLOR::WHITE) ? E_PIECE::wP : E_PIECE::bP);
    }
    

    assert (board.posHashKey == histData.posHashKey);
    assert (board.posHashKey == HASH.GenerateHash(board));
}



 