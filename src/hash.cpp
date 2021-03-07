#include "header.h"
#include <chrono> 
#include <random> 

/** Initialise Hash Values for each piece-square pairs and other flags
 * 
 *  @param  None
 *  @return None
**/
void S_HASH::InitHash()
{
    U64 seed = std::chrono::system_clock::now().time_since_epoch().count(); 
    std::mt19937_64 randomGenerator(seed);

    for (U8 pce = E_PIECE::EMPTY; pce <= E_PIECE::bK; ++pce)
    {
        for (U8 sq120 = 0; sq120 < BOARD_SIZE; ++sq120)
        {
            pieceSquarePairHash[pce][sq120] = randomGenerator();
        }
    }

    for (U8 i = 0; i < 8; i++)
        epHash[i] = randomGenerator();
    
    for (U8 i = 0; i < 16; i++)
        castleHash[i] = randomGenerator();
    
    sideToMoveHash = randomGenerator();
}


/** Constructor that initialises hash values.
 * 
 *  @param  None
 *  @return None
**/
S_HASH::S_HASH()
{
    InitHash();    
}


/** Constructor that initialises hash values. Then Generates Hash Key for it.
 * 
 *  @param  board   The board to extract data for generating Hash key.
 *  @return None
**/
S_HASH::S_HASH(Board& board)
{
    InitHash();
    GenerateHash(board);
}


/** Generates Hash Key for the board.
 * 
 *  @param  board   The board to extract data for generating Hash key.
 *  @return         Returns the 64 bit hashkey for the position set to board's posHashKey. Return value need not be stored
**/
U64 S_HASH::GenerateHash(Board& board)
{
    U64 hashKey = 0;

    for (U8 sq120 = 0; sq120 < BOARD_SIZE; ++sq120)
    {
        U8 pce = board.GetPieceOnSquare(sq120);

        if (pce != E_PIECE::OFFBOARD && pce != E_PIECE::EMPTY)      // pce not empty ensured because we don't want to (un)hash EMPTY whenever we add/remove a piece
        {
            hashKey ^= pieceSquarePairHash[pce][sq120];
        }
    }

    if (board.GetSideToMove() == E_COLOR::BLACK)
        hashKey ^= sideToMoveHash;

    U8 epSq = board.GetEPSquare();

    if (epSq != E_SQUARE::Square_Invalid)
        hashKey ^= epHash[SQ2FILE(epSq)];
    
    hashKey ^= castleHash[board.GetCastleRights()];

    board.posHashKey = hashKey;

    return hashKey;
}



