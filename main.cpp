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
    int sq120 = A4;
    int file = SQ2FILE(sq120);
    int rank = SQ2RANK(sq120);
    int sq64 = SQ64(sq120);

    std::cout << "File " << SQ2FILE(sq120) << " Rank " << SQ2RANK(sq120) << " | " << " 64 based index " << SQ64(sq120) << std::endl;
    std::cout << "Verifying FR2SQ " << FR2SQ(file, rank) << " and sq120 is " << SQ120(sq64) << std::endl;
    return 0;
}
