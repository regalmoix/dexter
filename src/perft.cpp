#include "header.h"
#include <chrono>

long leafNodes;

/** Perf Testing Helper for a certain depth on the Board.
 *  
 *  @param      depth   The depth to search till
 *  @param      board   The board to search on
 *
 * 
**/
void Perft(int depth, Board& board) 
{
	if(depth == 0) 
    {
        leafNodes++;
        return;
    }	

    std::vector<Move> moveList;
    
    AllMoves(board, moveList);

    // evaluate(board);
    for (auto mv : moveList)
    { 
        if (!MakeMove(board, mv)) 
            continue;
        
        // printf("%c%d -> ",SQ2FILE(mv.fromSquare) + 'A' - 1, SQ2RANK(mv.fromSquare));
        // printf("%c%d \n" ,SQ2FILE(mv.toSquare) + 'A' - 1, SQ2RANK(mv.toSquare));
        // board.PrintBoard();
        // std::cout << std::endl;
        Perft(depth - 1, board);
        
        UnmakeMove(board);
        // assert (e == evaluate(board));
    }

    return;
}


/** Perf Testing for a certain depth on the Board. Prints breakdown of number of moves for each legal move in current position.
 *  
 *  @param      depth   The depth to search till
 *  @param      board   The board to search on
 *
 *  @return     The number of leafnodes at the given depth in complete search tree
 * 
**/
int PerftTest(int depth, Board& board) 
{
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
        printf("%c%d -> ",SQ2FILE(m.fromSquare) + 'A' - 1, SQ2RANK(m.fromSquare));
        printf("%c%d" ,SQ2FILE(m.toSquare) + 'A' - 1, SQ2RANK(m.toSquare));
        printf(" : %ld\n", oldnodes);
    }

	auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

	printf("\nPerft Complete : %ld Nodes\t[%fs]\t@ %lfKN/s\n",leafNodes, elapsed.count(), leafNodes/(1000*elapsed.count()));

    return leafNodes;
}












