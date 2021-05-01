#include "header.h"
#include <vector>
#include <functional>
#include <iostream>
#include <numeric>


const int PawnTable[64] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
10	,	10	,	0	,	-10	,	-10	,	0	,	10	,	10	,
5	,	0	,	0	,	5	,	5	,	0	,	0	,	5	,
0	,	0	,	10	,	20	,	20	,	10	,	0	,	0	,
5	,	5	,	5	,	10	,	10	,	5	,	5	,	5	,
10	,	10	,	10	,	20	,	20	,	10	,	10	,	10	,
20	,	20	,	20	,	30	,	30	,	20	,	20	,	20	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int KnightTable[64] = {
0	,	-10	,	0	,	0	,	0	,	0	,	-10	,	0	,
0	,	0	,	0	,	5	,	5	,	0	,	0	,	0	,
0	,	0	,	10	,	10	,	10	,	10	,	0	,	0	,
0	,	0	,	10	,	20	,	20	,	10	,	5	,	0	,
5	,	10	,	15	,	20	,	20	,	15	,	10	,	5	,
5	,	10	,	10	,	20	,	20	,	10	,	10	,	5	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0		
};

const int BishopTable[64] = {
0	,	0	,	-10	,	0	,	0	,	-10	,	0	,	0	,
0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int RookTable[64] = {
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
25	,	25	,	25	,	25	,	25	,	25	,	25	,	25	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0		
};

const int Mirror64[64] = {
56	,	57	,	58	,	59	,	60	,	61	,	62	,	63	,
48	,	49	,	50	,	51	,	52	,	53	,	54	,	55	,
40	,	41	,	42	,	43	,	44	,	45	,	46	,	47	,
32	,	33	,	34	,	35	,	36	,	37	,	38	,	39	,
24	,	25	,	26	,	27	,	28	,	29	,	30	,	31	,
16	,	17	,	18	,	19	,	20	,	21	,	22	,	23	,
8	,	9	,	10	,	11	,	12	,	13	,	14	,	15	,
0	,	1	,	2	,	3	,	4	,	5	,	6	,	7
};

#define MIRROR64(sq) (Mirror64[(sq)])

                                    // E,  P,   N,   B,   R,   Q,    K,     p,    n,    b,    r,    q,     k   
const std::vector<S16> pieceValues    {0, 100, 290, 310, 550, 950, 10000, -100, -290, -310, -550, -950, -10000};

S16 evaluate1(Board& board)
{
    U8 t_score = board.materialScore;
    if (board.GetSideToMove() == E_COLOR::BLACK)
        t_score = -board.materialScore;

    return t_score;
}


S16 evaluate(S_BOARD& board) 
{

    U8 t_score = board.materialScore;
	U8 pce = 0;
	
	pce = wP;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score += PawnTable[SQ64(sq)];
    }	

	pce = bP;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score -= PawnTable[MIRROR64(SQ64(sq))];
    }	
	

    pce = wN;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score += KnightTable[SQ64(sq)];
    }	

	pce = bN;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score -= KnightTable[MIRROR64(SQ64(sq))];
    }

    pce = wB;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score += BishopTable[SQ64(sq)];
    }	

	pce = bB;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score -= BishopTable[MIRROR64(SQ64(sq))];
    }
    
	pce = wR;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score += RookTable[SQ64(sq)];
    }	

	pce = bR;	
    for (U8 sq : board.GetSquareList(pce))
    {
        if (SQLEGAL(sq))
            t_score -= RookTable[MIRROR64(SQ64(sq))];
    }


    if(board.GetSideToMove() == BLACK) 
    {
		t_score = -t_score;
	} 

    return t_score;	
}

