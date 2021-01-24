/* Headers */
#include <iostream>
#include <vector>
#include <bitset>


/* Macros */


/* Function Declarations */

/* Structures and Classes */

typedef struct S_BOARD
{
    int plys;
    std::vector<HISTORY> moveHistory;

    int fiftyMoveRuleCount;
    int enPassantSquare;

    /*
        Piece Lists, Bitboards etc
    */    
} BOARD;

typedef struct S_HISTORY
{
    /* data */
    
}HISTORY;
