#include "header.h"
#include <fstream>

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


// Pass pointer reference, effectively pointer to a pointer
static void UCIPosition(Board*& board, const std::string& command)
{
    // Delete previous board on heap.
    if (board != nullptr)
        delete board;
    
    std::string fen = STARTFEN;

    // Find the index of moves, if it exists. Everything before this index and after position is the FEN string
    size_t found = command.find("moves");


    if (command.substr(9, 8) != "startpos")
        fen = STARTFEN;
    
    if (command.substr(9, 3) == "fen")
    {
        // Only capture the FEN string
        if (found != std::string::npos)
        {
            size_t  fenLength   = (found - 2) - 13 + 1;
            fen     = command.substr(13, fenLength);
        }

        // No Moves specified after FEN string
        else
        {
            fen  = command.substr(13);
        }
    }
        
    board   = new Board(fen);
    HASH.GenerateHash(*board);


    if (found != std::string::npos)
    {
        std::stringstream movesPlayed(command.substr(found + 6));

        std::string curr_move;
        while(getline(movesPlayed, curr_move, ' '))
        {
            Move m = parseMove(*board, curr_move);

            if (m == Move::Invalid_Move)
            {
                exit(-1);
            }

            MakeMove(*board, m);
        }
    }
}


static void UCIGo(Board*& board, Search*& search, const std::string& command)
{
    if (false)
        cout << command;

    if (board == nullptr)
        return;

    search              = new Search;
    search->timeMax     = 75000;


    size_t found = (board->GetSideToMove() == E_COLOR::WHITE) ? command.find("wtime") : command.find("btime") ;

    if (found != std::string::npos)
    {
        std::stringstream commandStream (command.substr(found + 6));
        
        std::string timeAlloted;
        getline(commandStream, timeAlloted, ' ');

        search->timeMax = std::stod(timeAlloted);

        found = command.find("movestogo");

        if (found != std::string::npos)
        {
            std::string movesToGo;
            std::stringstream commandStream (command.substr(found + 10));
            getline(commandStream, movesToGo, ' ');
            search->timeMax /= 1.05 * std::stod(movesToGo);
        }          
    }

    search->depthMax    = 18;
    search->startTime   = std::chrono::high_resolution_clock::now();
    search->SearchPosition(*board);

    delete search;
}


void UCILoop ()
{
    // Log the commands in a file
    // std::ofstream log;
    // log.open("commands.txt", std::ios::out);



    std::cout.setf(std::ios::unitbuf);

    std::string command = "";
    Search*     search  = nullptr;
    Board*      board   = nullptr;

    // Print the UCI Information.
    printf ("id name %s\nid author %s\nuciok\n", NAME, AUTHORS);

    while(true)
    {
        // Fetch the command from the standard input
        getline (cin, command);
        //log     << command << std::endl;

        if (command == "isready")
        {
            printf ("readyok\n");
            continue;
        }

        else if (command == "uci")
        {
            printf ("id name %s\nid author %s\nuciok\n", NAME, AUTHORS);
            continue;
        }

        else if (command == "quit")
        {
            break;
        }

        else if (command.substr(0, 8) == "position")
        {
            UCIPosition(board, command);
        }

        else if (command.substr(0,2) == "go")
        {
            UCIGo(board, search, command);
        }

        else if (command == "ucinewgame")
        {
            UCIPosition(board, "position " STARTFEN);
        }

        else
            continue;
    }
}
