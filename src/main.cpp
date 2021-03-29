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
    std::string STARTFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";    

    std::string FEN =   "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";    
    std::string FEN1 =  "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq a3 0 1";    
    std::string f =     "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    // std::string FEN2 = "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1";
    Board b(STARTFEN);
    HASH.GenerateHash(b);

    // for (U8 sq120 = 0; sq120 < BOARD_SIZE; ++sq120)
    // {
    //     for (U8 pce = E_PIECE::EMPTY; pce <= E_PIECE::bK; ++pce)
    //     {            
    //         printf("%lX   ", HASH.pieceSquarePairHash[pce][sq120]);
    //     }
    //     printf("\n");
    // }

    
    PerftTest(4,b);
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
