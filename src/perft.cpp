// perft.c

#include "header.h"
#include <chrono>

long leafNodes;

void Perft(int depth, Board& board) 
{
	if(depth == 0) 
    {
        leafNodes++;
        return;
    }	

    std::vector<Move> moveList;
    
    AllMoves(board, moveList);

    for (auto mv : moveList)
    { 
        if (!MakeMove(board, mv)) 
            continue;
        
        Perft(depth - 1, board);
        UnmakeMove(board);
    }

    return;
}


void PerftTest(int depth, Board& board) 
{
	board.PrintBoard();
	printf("\nStarting Test To Depth:%d\n",depth);	
	leafNodes = 0;

	auto start = std::chrono::high_resolution_clock::now();

    std::vector<S_MOVE> moveList;
    
    AllMoves(board, moveList);
    

	for(auto m : moveList) 
    {
        if (!MakeMove(board, m))  
            continue;

        long cumnodes = leafNodes;
        Perft(depth - 1, board);
        UnmakeMove(board);  

        long oldnodes = leafNodes - cumnodes;
        
        printf("move %ld : ", oldnodes);
        printf("%c%d -> ",SQ2FILE(m.fromSquare) + 'A' - 1, SQ2RANK(m.fromSquare));
        printf("%c%d \n" ,SQ2FILE(m.toSquare) + 'A' - 1, SQ2RANK(m.toSquare));
        std::cout << std::endl;
            
    }
	auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;


	printf("\nTest Complete : %ld nodes visited in %fs\n",leafNodes, elapsed.count());

    return;
}












