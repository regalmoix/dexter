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

    ResetBoard();
}


U8 S_BOARD::GetPieceOnSquare (U8 sq120)
{
    std::bitset<480> temp = 0;

    temp.set(sq120 * 4, 1);
    temp.set(sq120 * 4 + 1, 1);
    temp.set(sq120 * 4 + 2, 1);
    temp.set(sq120 * 4 + 3, 1);

    return ((temp & posBitBoard)>>(sq120 * 4)).to_ulong();
}


E_PIECE S_BOARD::SetPieceOnSquare (U8 sq120, E_PIECE piece, std::string mode = "normal")
{
    /** NOTE
     *
     *  Returns existing piece on square before overwriting
     *  Check if piece exists on a square before setting it.
     *  Disallow when piece to be put on square is of same color as existing piece.
     *  In "normal mode", all errors are caught. In "reset" mode, no errors are reported
    **/

    U8 currPce = GetPieceOnSquare(sq120);

    if (currPce == E_PIECE::OFFBOARD && mode != "reset")     // 2nd condition allows re-setting offboard to offboard. 1st condition doesnt allow overwriting 'offboard'
    {
        if (piece != E_PIECE::OFFBOARD)
        {
            std::cerr << "[ERROR] Setting onboard piece " << (int)piece << " to offboard square. Transaction incomplete.\n";
        }

        else
        {
            // Means currPiece and piece both are offboard.
            // No over writing needed.
        }

        return static_cast<E_PIECE>(currPce);
    }

    else if (currPce != E_PIECE::EMPTY && piece != E_PIECE::EMPTY && mode != "reset")
    {
        if ((currPce >= E_PIECE::bP) == (piece >= E_PIECE::bP))         // For a non-empty square, disallow overwriting pieces of same color
        {
            std::cerr << "[ERROR] Attempted overwriting " << piece << " on " << currPce << " of same color. Transaction incomplete.\n";
            return static_cast<E_PIECE>(currPce);
        }
    }

        // Set pieceLists appropriately.
        // [To Do] Using ModifySquareList() to add sq120 for 'piece' and del sq120 for 'currPce'. Check validity of both ops.


        // Set posBitBoard appropriately.
      posBitBoard[4 * sq120 + 0]  = piece & 1;
      posBitBoard[4 * sq120 + 1]  = piece & 2;
      posBitBoard[4 * sq120 + 2]  = piece & 4;
      posBitBoard[4 * sq120 + 3]  = piece & 8;


      return static_cast<E_PIECE>(currPce);



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
                    ModifySquareList(E_PIECE::wP,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'N' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wN);
                    ModifySquareList(E_PIECE::wN,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'B' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wB);
                    ModifySquareList(E_PIECE::wB,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'R' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wR);
                    ModifySquareList(E_PIECE::wR,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'Q' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wQ);
                    ModifySquareList(E_PIECE::wQ,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'K' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wK);
                    ModifySquareList(E_PIECE::wK,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }


                case 'p' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bP);
                    ModifySquareList(E_PIECE::bP,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'n' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bN);
                    ModifySquareList(E_PIECE::bN,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'b' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bB);
                    ModifySquareList(E_PIECE::bB,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'r' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bR);
                    ModifySquareList(E_PIECE::bR,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'q' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bQ);
                    ModifySquareList(E_PIECE::bQ,FR2SQ(curr_file,curr_rank),"add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'k' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bK);
                    ModifySquareList(E_PIECE::bK,FR2SQ(curr_file,curr_rank),"add");
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
    printf("50 move cnt  : %d\n", fiftyMoveRuleCount);
    printf("En Passant   : %c%d\n", SQ2FILE(enPassantSquare) ? (SQ2FILE(enPassantSquare) + 'a' - 1) : '0', SQ2RANK(enPassantSquare));
    // printf("Equality test: %d\n", SQ2RANK(enPassantSquare));
}


void S_BOARD::ResetBoard()
{
    /** NOTE
     *
     *  The following function is incomplete and must be regularly updated
     *  whenever the S_BOARD D.S. is changed.
     *
     *  Reset pieceLists also. and count piece etc etc.
    **/

    posBitBoard = 0;
    sideToMove = E_COLOR::BOTH;
    fiftyMoveRuleCount = 0;
    posHashKey = 0;
    castleRights = 0;
    enPassantSquare = E_SQUARE::Square_Invalid;
    plys = 0;

    for(int i = 0; i < 12; i++)
    {
      for(int j = 0; j < 10; j++)
      {
        pieceList[i][j] = Square_Invalid;
      }
    }


    for (int i = 0; i < 120; i++)
    {
        SetPieceOnSquare(i, E_PIECE::OFFBOARD, "reset");
    }

    for (int i = 0; i < 64; i++)
    {
        SetPieceOnSquare(SQ120(i), E_PIECE::EMPTY, "reset");
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


std::vector<U8> S_BOARD::GetSquareList(U8 piece)
{
    if (piece == E_PIECE::EMPTY)
    {
        std::vector<U8> sqList;

        for (int i = 0; i < 64; i++)
        {
            if (GetPieceOnSquare(static_cast<E_SQUARE>(SQ120(i))) == E_PIECE::EMPTY)
            {
                sqList.push_back(SQ120(i));
            }
        }

        return sqList;
    }

    // else if (E_PIECE::wP < piece && piece < E_PIECE::wK)
    // {
    //     std::vector<U8> sqList(pieceList[piece - 1], pieceList[piece - 1] + 10);
    //     return sqList;
    // }
    //
    // else if (E_PIECE::bP < piece &&  piece < E_PIECE::wK)
    // {
    //     std::vector<U8> sqList(pieceList[piece - 2], pieceList[piece - 2] + 10);
    //     return sqList;
    // }
    //
    // else if (piece == E_PIECE::wK)
    // {
    //     std::vector<U8> sqList(1, kingSq[E_COLOR::WHITE]);
    //     return sqList;
    // }
    //
    // else if (piece == E_PIECE::bK)
    // {
    //     std::vector<U8> sqList(1, kingSq[E_COLOR::BLACK]);
    //     return sqList;
    // }

    std::vector<U8> sqList(pieceList[piece - 1], pieceList[piece - 1] + 10);
    return sqList;
    // return {};
}


U8 S_BOARD::ModifySquareList(U8 piece, U8 sq120, std::string operation)
{
    /** NOTE
     *
     *  @param :    piece => the piece whose list is to be modified
     *              sq120 => 120 based square involved in operation
     *              operation => "add" or "del" to add square to pieceList or to remove it.
     *
     *  @return :   Some error code if sq120 cant be deleted or cant be added. Else return success code (or some other useful info)
     *
     *  Description : modify 'piecelist'
     *
     *  Reminder :  pieceList[x] is weirdly indexed to save space.
     *              for x = 0..4 => piece wP..wQ [ie piece 1..5]
     *              for x = 5..9 => piece bP..bQ [ie piece 7..11]
     *              piece EMPTY [piece 0] is not associated with any list
     *              piece wK or bK are associated with kingSq[] indexed by color.
    **/

    if(operation == "add")
    {
      int i = 0;

      while(i < 10 && pieceList[piece-1][i] != Square_Invalid)
      {
        i++;
      }

      pieceList[piece-1][i] = sq120;
    }

    else
    {
      int i = 0;

      while(i < 10 && pieceList[piece-1][i] != sq120)
      {
        i++;
      }

      pieceList[piece-1][i] = Square_Invalid;

      for(int j = i; j < 9; j++)
      {

        if(pieceList[piece-1][j]==Square_Invalid)
          break;
          
        pieceList[piece-1][j] = pieceList[piece-1][j+1];
      }
    }
    return 0;
}

void S_BOARD::PrintPieceList(){


  for(int i = 0; i < 12; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      printf("%d ",pieceList[i][j]);
    }
    printf("\n");
  }
}
