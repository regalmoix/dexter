/**
 *  This is in its early stages of development so please report bugs to us :)
 * 
 *  Authors : Nachiket Agrawal, Tanish Agrawal 
 * 
 *  Date    : Jan 24, 2021 
 * 
 *
**/ 

#include "header.h"

int main()
{
    /*
    int sq120 = A4;
    int file = SQ2FILE(sq120);
    int rank = SQ2RANK(sq120);
    int sq64 = SQ64(sq120);

    std::cout << "File " << SQ2FILE(sq120) << " Rank " << SQ2RANK(sq120) << " | " << " 64 based index " << SQ64(sq120) << std::endl;
    std::cout << "Verifying FR2SQ " << FR2SQ(file, rank) << " and sq120 is " << SQ120(sq64) << std::endl;
    return 0;
    

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (i%10 == 0)  printf("\n");
        printf("%5d,", SQ64(i));
    }

    */
    //std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::string FEN = "3r1b1r/pp2nb2/3k1n1p/2Qp1B2/3P2P1/N4N1P/PP3P2/2R2RK1 b - - 0 20";
    //std::cin >> FEN;

    Board gameBoard(FEN);

    std::cout << "[]][][ " << gameBoard.posBitBoard << std::endl;

    gameBoard.PrintBoard();


}
