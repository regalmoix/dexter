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
    // cout << FR2SQ(1, 7) << endl;
    std::string mv;
   

    std::string STARTFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";    

    std::string FEN =   "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";    
    std::string FEN1 =  "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq a3 0 1";    
    std::string f =     "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    std::string Mate = "1k2r2r/ppp2p1p/3p1np1/1q1p4/3P1b2/1PQ2PN1/PBP1P1PP/RN2K2R b KQ - 0 1";
    std::string Mate4 = "2rr3k/pp3pp1/1nnqbN1p/3pN3/2pP4/2P3Q1/PPB4P/R4RK1 w - - 0 1";
    // std::string FEN2 = "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1";
    Board b("r4rk1/1qpp2pp/bp6/p2P1P2/P4pP1/5Q2/B1P4R/2K4R w - - 0 1");
    HASH.GenerateHash(b);
    Search search;
    search.depthMax = 11;
    search.Search_f(b);

    

    // cout << evaluate(b) << endl;
    // while (true)
    // {   
    //     cin >> mv;
    //     parseMove(b, mv);
    // }
    

    // for (U8 sq120 = 0; sq120 < BOARD_SIZE; ++sq120)
    // {
    //     for (U8 pce = E_PIECE::EMPTY; pce <= E_PIECE::bK; ++pce)
    //     {            
    //         printf("%lX   ", HASH.pieceSquarePairHash[pce][sq120]);
    //     }
    //     printf("\n");
    // }

    
    // PerftTest(4,b);
    return 0;

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
  
    return 0;
}
