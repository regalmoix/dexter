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

    std::string mv;
   

    std::string STARTFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";    

    std::string FEN     = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";    
    std::string FEN1    = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq a3 0 1";    
    std::string f       = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    std::string Mate    = "1k2r2r/ppp2p1p/3p1np1/1q1p4/3P1b2/1PQ2PN1/PBP1P1PP/RN2K2R b KQ - 0 1";
    std::string Mate4   = "2rr3k/pp3pp1/1nnqbN1p/3pN3/2pP4/2P3Q1/PPB4P/R4RK1 w - - 0 1";
    std::string FEN2    = "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1";

    Board c("r4rk1/1qpp2pp/bp6/p2P1P2/P4pP1/5Q2/B1P4R/2K4R w - - 0 1");
    Board d ("r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1");
    Board e("1k2r2r/ppp2p1p/3p1np1/1q1p4/3P4/1PQ2Pb1/PBP1P1PP/RN1K3R b - - 1 2");
    Board f1("6k1/ppp2pp1/1q4b1/5rQp/8/1P6/PBP2PPP/3R2K1 w Q - 0 1");


    UCILoop();

    // Board b("rb3K2/p1p5/P1Pp4/3N2k1/3N2nr/6n1/8/7Q w - - 0 1");
 

    // search.SearchPosition(b);

    // cout << "\n\n\n";
    // search.SearchPosition(c);
    // cout << "\n\n\n";
    // search.SearchPosition(d);
    // cout << "\n\n\n";
    // search.SearchPosition(e);
    // cout << "\n\n\n";
    // search.SearchPosition(f1);
    // cout << "\n\n\n";
    // b.PrintBoard();
    // std::cout << "Eval :" << evaluate(b) << " Mat Score : " << evaluate1(b)  << endl << endl;
    // int n = 6;
    // while (n--)
    // {
    //     string s;
    //     cin >> s;
    //     MakeMove(b, parseMove(b, s));
    //     b.PrintBoard();
    //     std::cout << "Eval :" << evaluate(b) << " Mat Score : " << evaluate(b)  << endl << endl;
    // }

    return 0;
}
