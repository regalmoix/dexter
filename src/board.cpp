#include "header.h"

char sq120To64[120] = 
{
    99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
    99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
    99,    0,    1,    2,    3,    4,    5,    6,    7,   99,
    99,    8,    9,   10,   11,   12,   13,   14,   15,   99,
    99,   16,   17,   18,   19,   20,   21,   22,   23,   99,
    99,   24,   25,   26,   27,   28,   29,   30,   31,   99,
    99,   32,   33,   34,   35,   36,   37,   38,   39,   99,
    99,   40,   41,   42,   43,   44,   45,   46,   47,   99,
    99,   48,   49,   50,   51,   52,   53,   54,   55,   99,
    99,   56,   57,   58,   59,   60,   61,   62,   63,   99,
    99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
    99,   99,   99,   99,   99,   99,   99,   99,   99,   99
};


S_BOARD::S_BOARD(std::string fenString) : S_BOARD::S_BOARD()
{
    /** NOTE
     *  
     *  Delegating Constructor used.
     *  S_BOARD() called first then control returned to S_BOARD(std::string s)
    **/
    ParseFen(fenString);
}


S_BOARD::S_BOARD()
{
    posBitBoard = 0;
    sideToMove = E_COLOR::BOTH;
    fiftyMoveRuleCount = 0;
    posHashKey = 0;
    castleRights = 0;
    enPassantSquare = E_SQUARE::Square_Invalid;
    plys = 0;

    ResetBoard();
}


int S_BOARD::GetPieceOnSquare (E_SQUARE sq120)
{
    std::bitset<480> temp = 0;

    temp.set(sq120 * 4, 1);
    temp.set(sq120 * 4 + 1, 1);
    temp.set(sq120 * 4 + 2, 1);
    temp.set(sq120 * 4 + 3, 1);

    return ((temp & posBitBoard)>>(sq120 * 4)).to_ulong();
}


void S_BOARD::SetPieceOnSquare (int sq120, E_PIECE piece)
{
    posBitBoard[4 * sq120 + 0]  = piece & 1;
    posBitBoard[4 * sq120 + 1]  = piece & 2;
    posBitBoard[4 * sq120 + 2]  = piece & 4;
    posBitBoard[4 * sq120 + 3]  = piece & 8; 

    // Also set pawn bit boards and piece lists if piece == wP or bP
    // Handle Captures? Maybe return existing piece before setting new piece?
}


void S_BOARD::ParseFen (std::string fenString)
{
    std::vector <std::string> fenStringTokens;
    std::stringstream fenStream (fenString);
    std::string token;

    while (getline(fenStream, token, ' ')) 
    { 
        fenStringTokens.push_back(token); 
    }

    // fenStringTokens[0] => '/' delimited string of pieces on a rank
    std::stringstream rankStream (fenStringTokens[0]);
    std::string rankInfo;

    int curr_rank = E_RANK::Rank_8;
    while (getline(rankStream, rankInfo, '/'))
    {
        std::string::iterator it = rankInfo.begin();
        int curr_file  = E_FILE::File_A;

        while ((curr_file <= E_FILE::File_H) && (it != rankInfo.end()))
        {
            char c = *it;

            switch (c)
            {
                case 'P' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wP);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'N' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wN);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'B' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wB);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'R' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wR);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'Q' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wQ);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'K' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wK);
                    ++ curr_file;
                    ++ it;   
                    break;
                }


                case 'p' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bP);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'n' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bN);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'b' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bB);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'r' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bR);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'q' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bQ);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                case 'k' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bK);
                    ++ curr_file;
                    ++ it;   
                    break;
                }

                default :
                {
                    assert (c >= '1' && c <= '8');
                    
                    for (int i = 0; i < c - '0'; ++i)
                    {
                        SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::EMPTY);
                        ++ curr_file;
                    }
                    ++it;
                    break;
                }
            } 
        }
        curr_rank --;
    }

    // fenStringTokens[1] => side to move
    assert (fenStringTokens[1] == "w" || fenStringTokens[1] == "b");
    sideToMove = (fenStringTokens[1] == "w") ? E_COLOR::WHITE : E_COLOR::BLACK;


    // fenStringTokens[2] => castle rights
    castleRights = 0;
    for (char& c : fenStringTokens[2])
    {
        switch (c)
        {
            case 'K' : 
            {
                castleRights |= E_CASTLE_RIGHTS::wK_castle;
                break;
            }

            case 'Q' : 
            {
                castleRights |= E_CASTLE_RIGHTS::wQ_castle;
                break;
            }

            case 'k' : 
            {
                castleRights |= E_CASTLE_RIGHTS::bK_castle;
                break;
            }

            case 'q' : 
            {
                castleRights |= E_CASTLE_RIGHTS::bQ_castle;
                break;
            }
        }
    }


    // fenStringTokens[3] => enPassant square
    enPassantSquare = Square_Invalid;
    if  (fenStringTokens[3] != "-")
    {
        enPassantSquare = static_cast<E_SQUARE> (FR2SQ (fenStringTokens[3][0] - 'a' + 1, fenStringTokens[3][1] - '1' + 1));
    }


    // fenStringTokens[4] => 50 move rule plys
    fiftyMoveRuleCount = std::stoi(fenStringTokens[4]);


    // fenStringTokens[5] => Num of fullmoves, incremented after Black plays
    plys = 2 * std::stoi(fenStringTokens[5]) + sideToMove - 2; 
}


void S_BOARD::PrintBoard ()
{   
    /*
        std::cout << "EnPass " << enPassantSquare << " && Castle " << (int)castleRights << std::endl;

        std::cout << "Side to move " << sideToMove << " && ply " << plys << std::endl;

        std::cout << "Pos " << posBitBoard << std::endl;
    */

    for (int rank = E_RANK::Rank_8; rank >= E_RANK::Rank_1; rank--)
    {
        for (int file = E_FILE::File_A; file <= E_FILE::File_H; file++)
        {
            E_SQUARE sq = static_cast<E_SQUARE>(FR2SQ(file, rank));

            int pce = GetPieceOnSquare(sq);

            char x;

            switch (pce)
            {
                case EMPTY : 
                {
                    x = '-';
                    break;
                }

                case wP : 
                {
                    x = 'P';
                    break;
                }

                case wN : 
                {
                    x = 'N';
                    break;
                }

                case wB : 
                {
                    x = 'B';
                    break;
                }

                case wR : 
                {
                    x = 'R';
                    break;
                }

                case wQ : 
                {
                    x = 'Q';
                    break;
                }

                case wK : 
                {
                    x = 'K';
                    break;
                }

                case bP : 
                {
                    x = 'p';
                    break;
                }

                case bN : 
                {
                    x = 'n';
                    break;
                }

                case bB : 
                {
                    x = 'b';
                    break;
                }

                case bR : 
                {
                    x = 'r';
                    break;
                }

                case bQ : 
                {
                    x = 'q';
                    break;
                }

                case bK : 
                {
                    x = 'k';
                    break;
                }

                case OFFBOARD :
                {
                    x = 'X';
                    break;
                }
            }
            printf("%2c", x);
        }
        printf("\n");    
    }
    printf("\n\n");

    printf("Side To Move : %c\n", sideToMove == E_COLOR::WHITE ? 'W' : 'B');
    printf("Castle       : %d\n", castleRights);
    printf("Plys         : %d\n", plys);
    printf("En Passant   : %c%d\n", SQ2FILE(enPassantSquare)+ 'a' - 1, SQ2RANK(enPassantSquare));
}


void S_BOARD::ResetBoard()
{
    /** NOTE
     *
     *  The following function is incomplete and must be regularly updated
     *  whenever the S_BOARD D.S. is changed.
    **/

    for (int i = 0; i < 480; i++)
    {
        posBitBoard.set(i, 1);
    }

    for (int i = 0; i < 64; i++)
    {
        SetPieceOnSquare(SQ120(i), EMPTY);
    }
}


void S_BOARD::PrintBoard120 ()
{   
    /*
        std::cout << "EnPass " << enPassantSquare << " && Castle " << (int)castleRights << std::endl;

        std::cout << "Side to move " << sideToMove << " && ply " << plys << std::endl;

        std::cout << "Pos " << posBitBoard << std::endl;
    */
    for (int i = 0; i < 120; i++)
    {
        if (i % 10 == 0)
            printf("\n");
        
        E_SQUARE sq = static_cast<E_SQUARE> ((i));

        int pce = GetPieceOnSquare(sq);
        char x;

        switch (pce)
        {
            case EMPTY : 
            {
                x = ' ';
                break;
            }

            case wP : 
            {
                x = 'P';
                break;
            }

            case wN : 
            {
                x = 'N';
                break;
            }

            case wB : 
            {
                x = 'B';
                break;
            }

            case wR : 
            {
                x = 'R';
                break;
            }

            case wQ : 
            {
                x = 'Q';
                break;
            }

            case wK : 
            {
                x = 'K';
                break;
            }

            case bP : 
            {
                x = 'p';
                break;
            }

            case bN : 
            {
                x = 'n';
                break;
            }

            case bB : 
            {
                x = 'b';
                break;
            }

            case bR : 
            {
                x = 'r';
                break;
            }

            case bQ : 
            {
                x = 'q';
                break;
            }

            case bK : 
            {
                x = 'k';
                break;
            }

            case OFFBOARD :
            {
                x = 'X';
                break;
            }
        }
        printf("%3c", x);

    }

    printf("\n");
}
