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


/** Parse the perft file and run PerftTest to check for anomalies
 *  
 *  @param      None
 *
 *  @return     None
 * 
**/
void PerftParser()
{

    using namespace std;

    vector<string> fens;

    string item_name;
    ifstream nameFileout;
    nameFileout.open("perftsuite.txt");
    string temp;
    vector<string> lines;
    while(std::getline(nameFileout, temp))
    {
        lines.push_back(temp);
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
  
}










