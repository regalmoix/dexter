#ifndef HEADERS_H   
#define HEADERS_H
#define NDEBUG
/** INCLUDES **/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <bitset>
#include <cstdio>
#include <sstream>
#include <assert.h>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <fstream>

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
typedef short int               S16;
typedef char                    S8;
typedef struct S_BOARD          Board;



/** MACRO EXPANSIONS **/

#define NAME                    "Dexter 1.0.0"
#define BOARD_SIZE              (120)
#define MAX_MOVES               (2048)
#define FR2SQ(f, r)             (10 + ((r) * 10) + (f))                                     // Convert File, Rank to 120 based Square indexing
#define SQ120(sq64)             (10 + ((sq64 / 8 + 1) * 10) + (sq64 % 8 + 1))               // Given Square in 64  based indexing convert to 120 based indexing
#define SQ64(sq120)             (sq120To64[sq120])                                          // Given Square in 120 based indexing convert to 64  based indexing
#define SQLEGAL(sq120)          (sq120To64[sq120] != Square_Invalid)
#define PIECECOLOR(pce)         ((wP <= pce && pce <= wK) ? WHITE : ((bP <= pce && pce <= bK) ? BLACK : BOTH))
#define SQ2FILE(sq120)          ((sq120 != Square_Invalid) ? (sq120 % 10) : 0)              // Given square in 120 indexing, find corresponding file
#define SQ2RANK(sq120)          ((sq120 != Square_Invalid) ? (((sq120) / 10) - 1) : 0)      // Given square in 120 indexing, find corresponding rank


// Pack info (check, enPassant, pawnDoublePush, CastleType, promotion, promotedPiece) to U8
#define PACKMOVE(CHK, EP, DP, CA, P, PP) \
                                ((CHK) << 7 | (EP) << 6 | (DP) << 5 | (CA) << 3 | (P) << 2 | (PP))
                                
// Pack info of current piece and captured piece to U8 for S_Move
#define PACKPIECEINFO(myPiece, capPiece) \
                                (((capPiece) << 4) | (myPiece))


/** ENUMERATIONS **/

enum E_PIECE : U8
{
    EMPTY,
    wP, wN, wB, wR, wQ, wK,
    bP, bN, bB, bR, bQ, bK,
    OFFBOARD = 15
};

enum E_PROMPIECE : U8
{
    Prom_N, Prom_B, Prom_R, Prom_Q
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
    Square_Invalid = 99
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

/** STRUCTS | CLASSES **/

typedef struct S_MOVE
{
    S16                     score;
    U8                      fromSquare;
    U8                      toSquare;
    U8                      pieceInfo;                      // 4 bits each for moving/curr piece[3..0] and captured piece [7..4]
    U8                      moveData;

    /** NOTE
     *
     *  Bit representation format of moveData.
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

    bool isCapture();

    bool isEPCapture();

    bool isCheck();

    bool isPawnDoublePush();

    bool isPromotion();

    E_PIECE getPromotedPiece();

    void setAttributes (U8 moveInfo);

    void unsetAttributes (U8 moveInfo);

    U8 getMovingPiece();

    U8 getCapturedPiece();

    U8 getCastle();

    S_MOVE (Board& board, U8 from, U8 to);                                            // Assume QUIET Move

    S_MOVE (Board& board, U8 from, U8 to, U8 moveInfo);

    S_MOVE (U8 from, U8 to, U8 moveInfo, U8 pieceInfo);


    // void operator = (S_MOVE& other) 
    // { 
    //     std::cout << "Hi" << std::endl;
    //     this->score         = other.score;
    //     this->fromSquare    = other.fromSquare;
    //     this->toSquare      = other.toSquare;
    //     this->pieceInfo     = other.pieceInfo;
    //     this->moveData      = other.moveData;
    // }

} Move;

typedef struct S_HISTORY
{
public:
    Move                    move;                           // What move was played
    U64                     posHashKey;                     // Hashkey of position when(after??) the move was made
    U8                      enPassantSquare;                // En Passant Square
    U8                      castlePermissions;              // Castle Permissions when (after??) this move is made
    U8                      fiftyCount;                     // Num moves since last capture / pawn push

    S_HISTORY(Move move, U64 posHashKey, U8 enPassantSquare, U8 castlePermissions, U8 fiftyCount) : move(move)
    {
        this->posHashKey = posHashKey;
        this->fiftyCount = fiftyCount;
        this->enPassantSquare = enPassantSquare;
        this->castlePermissions = castlePermissions;
    }

} History;

typedef struct S_BOARD
{
    
/** DESCRIPTION
 *
 *  This Data Structure aims to store all properties that uniquely define a board
 *  Additional properties are stored with aim of improving calculations at cost of memory
 *  Additionally, member functions to assist with D.S. manipulation are WIP
**/

public :
    U16                     plys;
    U8                      sideToMove;
    U8                      fiftyMoveRuleCount;             // Moves since last capture. If >50 then draw.
    U8                      enPassantSquare;
    U8                      castleRights;                   // Bitwise OR of E_CASTLE_RIGHTS

    std::vector<History>    moveHistory;

    std::array<std::vector<U8>, 12>     pieceList;    
    // std::array<U8, 13>               countPiece;                     // UNUSED ?     //ResetBoard, AddPiece, RemovePiece
    std::bitset<480>                    posBitBoard;                    // Color independant. 4bits per square * 120 squares
    U8                                  brd_array[BOARD_SIZE];
    S16                                 materialScore;
    U64                                 posHashKey;

public :
    S_BOARD();

    S_BOARD(std::string fenString);

    U8 GetPieceOnSquare (U8 sq120);

    E_PIECE SetPieceOnSquare (U8 sq120, E_PIECE piece);

    void ParseFen (std::string fenString);

    void PrintBoard ();

    void PrintBoard120 ();

    void PrintPieceList ();

    void PrintPieceList2 ();

    void ResetBoard ();

    std::vector<U8> GetSquareList (U8 piece);

    U8 ModifySquareList (U8 piece, U8 sq120, std::string operation);

    U8 GetSideToMove ();

    U8 GetEPSquare ();

    U8 GetCastleRights ();

} Board;

typedef struct S_HASH
{
    U64                                         sideToMoveHash;
    std::array<std::array<U64, BOARD_SIZE>, 13> pieceSquarePairHash;
    std::array<U64, 9>                          epHash;                     // 9 since we index by file which is 1 to 8. epHash[0] unused
    std::array<U64, 16>                         castleHash;
    
    void InitHash();

    U64 GenerateHash(Board& board);

    S_HASH();

    S_HASH(Board& board);

} S_HASH;  

typedef struct S_SEARCH
{

public:
    U8      depthMax;
    U8      depth;
    U8      movesTillTimeControl;
    U64     nodesSearched;                                                      // Could be used to estimate search speed
    bool    quit;                                                               // GUI requested to quit
    bool    stopped;                                                            // If search is over/stopped 
    std::vector <std::vector<Move>> principalVariation;

    std::chrono::_V2::system_clock::time_point  startTime;
    std::chrono::_V2::system_clock::time_point  stopTime;
    std::chrono::duration<double>               timeMax;

    S_SEARCH(Board board) : depthMax(1), depth(1), movesTillTimeControl(0), nodesSearched(0), quit(false), stopped(false)
    {
        Move Invalid_Move (board, E_SQUARE::Square_Invalid, E_SQUARE::Square_Invalid);

        principalVariation.resize(25);

        // for (auto& pv : principalVariation)
        // {
        //     for (int i = 0; i < 25; i++)
        //     {
        //         pv.push_back(Invalid_Move);
        //     }
        // }   
    }

    void    SearchPosition  (Board& board);                                         // Iterative Deepening
    S16     AlphaBeta       (Board& board, S16 alpha, S16 beta, U8 currDepth, std::vector<Move>& pv);      // Alpha Beta Pruning Search till a depth
    S16     Quiescence      (Board& board, S16 alpha, S16 beta);                    // Search, irrespective of depth, all capture moves till we see a quiet move

} Search;

/** GLOBAL VARIABLES **/

extern char sq120To64[];
extern S_HASH HASH;
extern const std::vector<S16> pieceValues;


/** FUNCTION DECLARATIONS **/

extern bool isAttacked          (Board& board, U8 sq120, S8 attackingside = (S8)(-1));
extern void AllMoves            (Board& board, std::vector<S_MOVE>& moveList);
extern void addQuietMove        (Board& board, Move& move, std::vector<S_MOVE>& moveList);
extern void addCaptureMove      (Board& board, Move& move, std::vector<S_MOVE>& moveList);
extern bool MakeMove            (Board& board, Move move);
extern void UnmakeMove          (Board& board);
extern int  PerftTest           (int depth, Board& board);
extern void Perft               (int depth, Board& board);
extern void PerftParser         ();
extern S_MOVE parseMove         (Board& board, std::string& moveInput);
extern S16 evaluate             (Board& board);
#endif
