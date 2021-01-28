/** DEXTER 1.0.0 
 * 
 *  This is in its early stages of development so please report bugs to us :)
 * 
 *  Authors : Nachiket Agrawal, Tanish Agrawal 
 * 
 *  Date    : Jan 24, 2021 
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

    
    //std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::string FEN = "3r1b1r/pp2nb2/3k1n1p/2Qp1B2/3P2P1/N4N1P/PP3P2/2R2RK1 b - - 0 20";
    //std::cin >> FEN;

    Board gameBoard(FEN);

    std::cout << "[]][][ " << gameBoard.posBitBoard << std::endl;

    gameBoard.PrintBoard();

    */

    std::string FEN = "1r1q2k1/1r1n1p1p/3Pp1p1/R7/5P2/1PQ2B2/2P4P/1K1R4 b - - 4 30";
    //std::string FEN = "R7/8/8/8/8/8/8/8 w KQkq - 0 1";


    getline(std::cin, FEN);
    Board b(FEN);

    //b.PrintBoard();
    //b.SetPieceOnSquare(FR2SQ(1,8), E_PIECE::wR);
    //std::cout << "Details of A1 square : " << b.posBitBoard[A1*4 + 3] << b.posBitBoard[A1*4 + 2] << b.posBitBoard[A1*4 + 1] << b.posBitBoard[A1*4 + 0] << std::endl;
    //b.SetPieceOnSquare(H3, bK);
    // std::cout << "Details of H3 square : " << b.posBitBoard[H3*4 + 3] << b.posBitBoard[H3*4 + 2] << b.posBitBoard[H3*4 + 1] << b.posBitBoard[H3*4 + 0] << std::endl;
    // std::bitset<480> temp = 0xF << 192;

    printf("\n\nPrintBoard : \n");
    b.PrintBoard();
    

    // printf("\n\nPrintBoard2 : \n");
    // b.PrintBoard120();
    // std :: cout << "temp is " << temp.to_string(); 
    // unsigned long long x = ((temp & b.posBitBoard) >> 192).to_ullong();
    // std :: cout << "x is " << x << std::endl;

    return 0;
}
