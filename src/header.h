#ifndef HEADERS_H
#define HEADERS_H

/** INCLUDES **/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <bitset>
#include <cstdio>
#include <sstream>
#include <cassert>
#include <unordered_set>

using std::vector;
using std::array;
using std::cout;
using std::endl;
using std::cin;


/** ALIASES **/

typedef unsigned long int       U64;
typedef unsigned int            U32;
typedef unsigned short int      U16;
typedef unsigned char           U8;
typedef std::unordered_set<U8>  U8set;


/** MACRO EXPANSIONS **/

#define NAME                    "Dexter 1.0.0"
#define BOARD_SIZE              (120)
#define MAX_MOVES               (2048)
#define FR2SQ(f, r)             (10 + ((r) * 10) + (f))                             // Convert File, Rank to 120 based Square indexing
#define SQ2FILE(sq120)          ((sq120 % 10)*(sq120 != Square_Invalid))            // Given square in 120 indexing, find corresponding file
#define SQ2RANK(sq120)          ((((sq120) / 10) - 1)*(sq120 != Square_Invalid))    // Given square in 120 indexing, find corresponding rank
#define SQ120(sq64)             (10 + ((sq64 / 8 + 1) * 10) + (sq64 % 8 + 1))       // Given Square in 64  based indexing convert to 120 based indexing
#define SQ64(sq120)             sq120To64[sq120]                                    // Given Square in 120 based indexing convert to 64  based indexing

/** ALTERNATE/BUGGY CODE
    Given Square in 120 based indexing convert to 64  based indexing

    #define SQ64(sq120)             ((sq120 % 10 == 0) || (sq120 % 10 == 9) ||  \
                                    (sq120 < 20) || (sq120 > 99)) ?  99 :       \
                                    ((8*((sq120)/10))+((sq120)%10)-17)


    #define SQ64(sq120)           ((8*((sq120)/10))+((sq120)%10)-17)
**/


/** ENUMERATIONS **/

enum E_PIECE : U8
{
    EMPTY,
    wP, wN, wB, wR, wQ, wK,
    bP, bN, bB, bR, bQ, bK,
    OFFBOARD = 15
};

enum E_RANK : U8
{
    RankInvalid,
    Rank_1, Rank_2, Rank_3, Rank_4, Rank_5, Rank_6, Rank_7, Rank_8
};

enum E_FILE : U8
{
    File_Invalid,
    File_A, File_B, File_C, File_D, File_E, File_F, File_G, File_H
};

enum E_SQUARE : U8
{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    Square_Invalid
};

enum E_COLOR : U8
{
    WHITE, BLACK, BOTH
};

enum E_CASTLE_RIGHTS : U8
{
    wK_castle = 1,
    wQ_castle = 2,
    bK_castle = 4,
    bQ_castle = 8
};


/** GLOBAL VARIABLES **/

extern char sq120To64[];


/** FUNCTION DECLARATIONS **/


/** STRUCTS | CLASSES **/

typedef struct S_HISTORY
{
    U64                     move;                           // What move was played
    U64                     posHashKey;                     // Hashkey of position when(after??) the move was made
    U8                      enPassantSquare;                // En Passant Square
    U8                      castlePermissions;              // Castle Permissions when (after??) this move is made

} History;

typedef struct S_BOARD
{
    /** DESCRIPTION
     *
     *  This Data Structure aims to store all properties that uniquely define a board
     *  Additional properties are stored with aim of improving calculations at cost of memory
     *  Additionally, member functions to assist with D.S. manipulation are WIP
    **/

private :

    U64                     posHashKey;
    U16                     plys;
    U8                      sideToMove;
    U8                      fiftyMoveRuleCount;             // Moves since last capture. If >50 then draw.
    U8                      enPassantSquare;
    U8                      castleRights;                   // Bitwise OR of E_CASTLE_RIGHTS

    std::vector<History>    moveHistory;

    /** Piece Lists, Bitboards
     *
     *  To store pawns in bitboards? Currently removed, saves 24 Bytes. :)
     *  Piece List ? yes => update functions : no => any disadvantage?
     *  Using standard arrays for piece lists to save on memory
    **/

    U8                      kingSq[2];
    U8                      pieceList[12][10];              // pceList[pce] stores array of squares where Pce exists
    std::array<U8, 13>      countPiece;                     // Count Pieces of each type and color.
    std::bitset<480>        posBitBoard;                    // Color independant. 4bits per square * 120 squares

    /** NOTE
     *
     *  120 * 4 = 480. Bits 0:3 = Sq 0 and Bits 4:7 = Sq 1 and so on...
     *  Hence Sq i means bits 4*i : 4*i + 3
    **/

    /** OPEN QUESTIONS
     *
     *  Do we store which squares the minor pieces are on?
     *  Do we store set of legal moves in the position? in a vector or LL?
     *  Does the generate moves (Set of) function(s) reside as a member function?
     *  How to modularise
    **/

    /** TODO
     *
     *  Assert in constructor that sideToMove is W or B, not 'Both'
     *  Set bit of square X on pawn bitboard
     *  Function Prototypes to retrieve piece at given E_Square sq. [Check if sq is onboard]
     *  Function Prototypes to remove ''
     *  Function Prototypes to add    ''
     *  Much more
     *  Read and parse FEN
     *  Write Constructor
     *  Hashkey to detect 3-fold (player must claim draw) and 5-fold (forced draw) repetition
     *  Init pieceList while parsing FEN.
     *  Maintain consistency across member variables
    **/

public :

    S_BOARD();

    S_BOARD(std::string fenString);

    U8 GetPieceOnSquare (U8 sq120);

    E_PIECE SetPieceOnSquare (U8 sq120, E_PIECE piece, std::string mode);

    void ParseFen (std::string fenString);

    void PrintBoard ();

    void PrintBoard120 ();

    void PrintPieceList ();

    void PrintPieceList2 ();

    void ResetBoard ();

    std::vector<U8> GetSquareList(U8 piece);

    U8 ModifySquareList(U8 piece, U8 sq120, std::string operation);

} Board;


#endif
