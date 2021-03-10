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
#include <bits/stdc++.h>
using namespace std;
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


    // std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::string FEN = "3r1b1r/pp2nb2/3k1n1p/2Qp1B2/3P2P1/N4N1P/PP3P2/2R2RK1 b - - 0 20";
    //std::cin >> FEN;

    Board gameBoard(FEN);

    std::cout << "[]][][ " << gameBoard.posBitBoard << std::endl;

    gameBoard.PrintBoard();

    */


    // std::string FEN = "1r1q2k1/1r1n1p1p/3Pp1p1/R7/5P2/1PQ2B2/2P4P/1K1R4 b - h7 4 30";
    //std::string FEN = "R7/8/8/8/8/8/8/8 w KQkq - 0 1";

    // std::string FEN = "r2qkb1r/p1pb2pp/2n3n1/1pPppp1P/1Pb1P3/1r1K1N2/P2P1PPb/R3B2R w KQkq b6 0 9";
    // std::string FEN = "r4rk1/p2nbp1p/1qp1bpp1/3p4/3P4/2NBPN2/PPQ2PPP/R4RK1 w - - 0 1";
    //getline(std::cin, FEN);
    std::string STARTFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";    

    std::string FEN = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";    
    // std::string FEN2 = "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1";
    Board b(FEN);
    HASH.GenerateHash(b);

    std::vector<S_MOVE> mvList;
    // cout<<isAttacked(b,E_SQUARE::E2)<<"\n";
    // int d = 3;
    // cin >> d;
    cout<<"\n";
    // cout<<isAttacked(b,E_SQUARE::F6)<<"\n";

    // PerftTest(d,b);


    vector<string> fens;

    string item_name;
    ifstream nameFileout;
    nameFileout.open("perftsuite.txt");
    string temp;
    vector<string> lines;
    while(std::getline(nameFileout, temp))
    {
        lines.push_back(temp);
        // TODO: assign item_name based on line (or if the entire line is 
        // the item name, replace line with item_name in the code above)
    }

    for(std::size_t i = 0; i < lines.size();i++){
        string word = "";
        for(auto x : lines[i]){
            if(x==';'){
                fens.push_back(word);
                word = "";
                break;
            }
            else{
                word+=x;
            }
        }
    }

    vector<int> myDepths;

    for(std::size_t i = 0; i < fens.size(); i++){
        Board b(fens[i]);
        HASH.GenerateHash(b);
        int x = PerftTest(5, b);
        myDepths.push_back(x);
    }
    

    fstream file; 
    string word, t, q, filename; 
  
    // filename of the file 
    filename = "perftsuite.txt"; 
  
    // opening file 
    file.open(filename.c_str()); 
  
    // extracting words from the file 
    vector<int> depths;
    bool flag = false;
    while (file >> word) 
    { 
        if(flag){
            int val = stoi(word);
            depths.push_back(val);
            flag = false;
        }
        if(word==";D5"){
            flag = true;
        }
        
    } 


    cout<<"\n\n";
    for(std::size_t i = 0; i < myDepths.size(); i++){
        if(myDepths[i]!=depths[i]){
            cout<<i+1<<"\n";
        }
    }

    
    // AllMoves(b, mvList);
    // cout << (int)b.GetSquareList(E_PIECE::bK)[0] << endl;
    // cout << (int)b.GetSquareList(E_PIECE::wK)[0] << endl;
    // cout << isAttacked(b, b.GetSquareList(E_PIECE::bK)[0], E_COLOR::WHITE) << endl << endl;
    // for (auto m : mvList)
    // {
    //     if (!MakeMove(b, m))
    //     {
    //         printf("%c%d -> ",SQ2FILE(m.fromSquare) + 'A' - 1, SQ2RANK(m.fromSquare));
    //         printf("%c%d \n" ,SQ2FILE(m.toSquare) + 'A' - 1, SQ2RANK(m.toSquare));
    //         cout << "\nIllegal\n";
    //         continue;
    //     }
    //     else
    //     {
    //         printf("%c%d -> ",SQ2FILE(m.fromSquare) + 'A' - 1, SQ2RANK(m.fromSquare));
    //         printf("%c%d \n" ,SQ2FILE(m.toSquare) + 'A' - 1, SQ2RANK(m.toSquare));
    //         b.PrintBoard();
    //         cout << endl;
    //         UnmakeMove(b);
    //         b.PrintBoard();
    //         cout << endl;
    //         cout << endl;
    //         cout << endl;
    //     }
    //     getchar();
    // }
    //b.PrintBoard();
    //b.SetPieceOnSquare(FR2SQ(1,8), E_PIECE::wR);
    //std::cout << "Details of A1 square : " << b.posBitBoard[A1*4 + 3] << b.posBitBoard[A1*4 + 2] << b.posBitBoard[A1*4 + 1] << b.posBitBoard[A1*4 + 0] << std::endl;
    //b.SetPieceOnSquare(H3, bK);
    // std::cout << "Details of H3 square : " << b.posBitBoard[H3*4 + 3] << b.posBitBoard[H3*4 + 2] << b.posBitBoard[H3*4 + 1] << b.posBitBoard[H3*4 + 0] << std::endl;
    // std::bitset<480> temp = 0xF << 192;
    // printf("\n\nPrintBoard : \n");
    // b.PrintBoard();
    // printf("\n\nPrint Piece List : \n");
    // b.PrintPieceList();
    // cout << endl;
    // b.PrintPieceList2();
    // cout << "size: " << sizeof(S_BOARD) << ", "  << sizeof(S_HISTORY) << ", " << sizeof(S_MOVE) << ", ";
    //b.SquareList(bK);
    // printf("\n\nPrintBoard2 : \n");
    // b.PrintBoard120();
    // std :: cout << "temp is " << temp.to_string();
    // unsigned long long x = ((temp & b.posBitBoard) >> 192).to_ullong();
    // std :: cout << "x is " << x << std::endl;
    // cout << "Pce on 78 ;" << (int)b.GetPieceOnSquare(78) << ";" << endl; 
    // PawnMoves(b);
    // cout << "\n\n\n";
    //
    // for (auto moves : moveList)
    // {
    //     // cout << (int)moves.fromSquare << " -> " << (int)moves.toSquare << endl;
    //     printf("%c%d -> ",SQ2FILE(moves.fromSquare) + 'A' - 1, SQ2RANK(moves.fromSquare));
    //     printf("%c%d \n" ,SQ2FILE(moves.toSquare) + 'A' - 1, SQ2RANK(moves.toSquare));
    //
    //
    // }
    // bool flag = isAttacked(b,E_SQUARE::D2);
    // cout<<flag<<"\n";
    // KnightMoves(b);
    // BishopMoves(b);
    // RookMoves(b);
    // QueenMoves(b);
    // KingMoves(b);
    // cout << "\n\n\n";
    // for (auto moves : moveList)
    // {
    //     // cout << (int)moves.fromSquare << " -> " << (int)moves.toSquare << endl;
    //     printf("%c%d -> ",SQ2FILE(moves.fromSquare) + 'A' - 1, SQ2RANK(moves.fromSquare));
    //     printf("%c%d \n" ,SQ2FILE(moves.toSquare) + 'A' - 1, SQ2RANK(moves.toSquare));
    // }
    // cout<<moveList.size()<<"\n";
    // for (U8 sq120 = 0; sq120 < BOARD_SIZE; ++sq120)
    // {
    //     for (U8 pce = E_PIECE::EMPTY; pce <= E_PIECE::bK; ++pce)
    //     {            
    //         printf("%X   ", Hash.pieceSquarePairHash[pce][sq120]);
    //     }
    //     printf("\n");
    // }
    
    return 0;
}
