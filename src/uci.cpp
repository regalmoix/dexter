#include "header.h"

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

void UCILoop ()
{
    printf ("id name %s\nid author %s\nuciok\n", NAME, AUTHORS);

    

    while(true)
    {
        Search search;
        search.depthMax = 7;
        
        fflush(stdout);
        std::string str;
        std::getline(cin, str);
        
        std::cout << "\nRecieved : [" << str << "]\n";

        if (str == "isready")
        {
            std::cout << "readyok" << std::endl;
            continue;
        }

        else if (str == "uci")
        {
            printf ("id name %s\nid author %s\nuciok\n", NAME, AUTHORS);
            continue;
        }

        else if (str == "ucinewgame")
        {
            Board b(STARTFEN);
            HASH.GenerateHash(b);
            search.SearchPosition(b);

            continue;
        }

        else if (str == "quit")
        {
            break;
        }

        else if (str.substr(0, 9) == "position ")
        {
            std::string fen = STARTFEN;

            if (str.substr(9, 8) != "startpos")
                fen = STARTFEN;
            
            if (str.substr(9, 4) == "fen ")
                fen = str.substr(13);

            Board b(fen);
            HASH.GenerateHash(b);

            size_t found = str.find("moves ");

            if (found != std::string::npos)
            {
                std::stringstream ss(str.substr(found+6));

                std::string curr_move;
                while(getline(ss, curr_move, ' '))
                {
                    Move m = parseMove(b, curr_move);

                    if (m == Move::Invalid_Move)
                    {
                        cout << "LOL";
                        exit(-1);
                    }

                    MakeMove(b, m);
                }
            }

            // printf("\n");
            // b.PrintBoard();
            // printf("\n");

            std::string go;
            std::getline(cin, go);

            
            search.SearchPosition(b);
        }

        else
        {
            continue;
        }
    }
}