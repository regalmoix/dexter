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


/** Contructor to Reset Board and init with FEN string
 *  
 *  @param      none
 *
 *  @return     none
 * 
**/
S_BOARD::S_BOARD(std::string fenString) : S_BOARD::S_BOARD()
{
    /** NOTE
     *
     *  Delegating Constructor used.
     *  S_BOARD() called first then control returned to S_BOARD(std::string s)
    **/
    ParseFen(fenString);
}


/** Contructor to Reset Board
 *  
 *  @param      none
 *
 *  @return     none
 * 
**/
S_BOARD::S_BOARD()
{
    ResetBoard();
}


/** Get the piece on the square.
 *  
 *  @param      sq120  120 based square involved in operation
 *
 *  @return     U8 piece that exists on the square
 * 
**/
U8 S_BOARD::GetPieceOnSquare (U8 sq120)
{
    return brd_array[sq120];
    // return (brd_array[sq120/2] & (0x0F + 0xE1*(sq120 & 1))) >> (4*(sq120 & 1));
}


/** Set the piece on the square.
 *  
 *  @param      sq120  120 based square involved in operation
 *  @param      piece  piece to set on square
 *  @param      mode   "normal" prevents overwriting of OFFBOARD squares. Also prevents capturing own pieces.
 *
 *  @return     U8 piece that exists on the square before updation.
 * 
 *  @todo       Remove useless error checking and move it to a useful place.
 * 
**/
E_PIECE S_BOARD::SetPieceOnSquare (U8 sq120, E_PIECE piece)
{
    U8 currPce = GetPieceOnSquare(sq120);
    brd_array[sq120] = piece;    
    return static_cast<E_PIECE>(currPce);
}


/** Parses FEN and sets member fields of the Data Structure appropriately.
 *  
 *  @param  fenstring The supplied FEN String
 *  
 *  @return None
**/
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
                    ModifySquareList(E_PIECE::wP, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'N' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wN);
                    ModifySquareList(E_PIECE::wN, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'B' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wB);
                    ModifySquareList(E_PIECE::wB, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'R' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wR);
                    ModifySquareList(E_PIECE::wR, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'Q' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wQ);
                    ModifySquareList(E_PIECE::wQ, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'K' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::wK);
                    ModifySquareList(E_PIECE::wK, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }


                case 'p' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bP);
                    ModifySquareList(E_PIECE::bP, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'n' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bN);
                    ModifySquareList(E_PIECE::bN, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'b' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bB);
                    ModifySquareList(E_PIECE::bB, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'r' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bR);
                    ModifySquareList(E_PIECE::bR, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'q' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bQ);
                    ModifySquareList(E_PIECE::bQ, FR2SQ(curr_file, curr_rank), "add");
                    ++ curr_file;
                    ++ it;
                    break;
                }

                case 'k' :
                {
                    SetPieceOnSquare(FR2SQ(curr_file, curr_rank), E_PIECE::bK);
                    ModifySquareList(E_PIECE::bK, FR2SQ(curr_file, curr_rank), "add");
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


/** Print the Board to console in Readable format
 *  
 *  @param  None
 *  @return None
**/
void S_BOARD::PrintBoard ()
{
    for (int rank = E_RANK::Rank_8; rank >= E_RANK::Rank_1; rank--)
    {
        std::cout << rank;

        for (int file = E_FILE::File_A; file <= E_FILE::File_H; file++)
        {
            E_SQUARE sq = static_cast<E_SQUARE>(FR2SQ(file, rank));

            int pce = GetPieceOnSquare(sq);

            char x = 'x';

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

    printf(" ");
    for (int f = 0; f < 8; f++)
    {
        printf("%2c", 'A' + f);
    }
    printf("\n\n");

    printf("Side To Move : %c\n", sideToMove == E_COLOR::WHITE ? 'W' : 'B');
    // printf("Castle       : %d\n", castleRights);
    // printf("Plys         : %d\n", plys);
    // printf("50 move cnt  : %d\n", fiftyMoveRuleCount);
    printf("En Passant   : %c%d\n", SQ2FILE(enPassantSquare) ? (SQ2FILE(enPassantSquare) + 'a' - 1) : '0', SQ2RANK(enPassantSquare));
}


/** Reset all data structure fields in an appropriate fashion.
 * 
 *  @param  None
 *  @return None
 * 
 *  @todo   Regularly Update this function as an when new variables get associated with the board
 * 
**/
void S_BOARD::ResetBoard()
{
    posBitBoard = 0;
    sideToMove = E_COLOR::BOTH;
    fiftyMoveRuleCount = 0;
    posHashKey = 0;
    castleRights = 0;
    enPassantSquare = E_SQUARE::Square_Invalid;
    plys = 0;

    for (int i = 0; i < 13; i++)
    {
        countPiece[i] = 0;
    }

    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            pieceList[i][j] = Square_Invalid;
        }
    }

    for (int i = 0; i < 120; i++)
    {
        SetPieceOnSquare(i, E_PIECE::OFFBOARD);
    }

    for (int i = 0; i < 64; i++)
    {
        SetPieceOnSquare(SQ120(i), E_PIECE::EMPTY);
    }


    // ALT PCELIST 
    for (int i = 0; i < 12; i++)
    {
        alt_pieceList[i].push_back(E_SQUARE::Square_Invalid);
    }

    for (int i = 0; i < BOARD_SIZE; i++)
        brd_array[i] = 0;
}


/** Alternative way to print the Board to console in Readable format
 *  
 *  @param  None
 *  @return None
**/
void S_BOARD::PrintBoard120 ()
{
    for (int i = 0; i < 120; i++)
    {
        if (i % 10 == 0)
            printf("\n");

        E_SQUARE sq = static_cast<E_SQUARE> ((i));

        int pce = GetPieceOnSquare(sq);
        char x = 'x';

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


/** Get the piecelist of all squares this piece is on.
 *  
 *  @param      piece  the piece whose list is to be retrieved
 *  @param      sq120  120 based square involved in operation
 *
 *  @return     std::vector<> of sq120 where piece exists.
 * 
 *  @todo       Remove all E_SQUARE::Square_Invalid from the returned
**/
std::vector<U8> S_BOARD::GetSquareList(U8 piece)
{
    if (piece == E_PIECE::EMPTY)
        return {};
    
    else if (alt_pieceList[piece-1].empty())
        assert(false);
    
    else 
        return alt_pieceList[piece-1];
    
    return {};
}


/** Modify piecelist which stores all squares a piece is on.
 *  
 *  @param      piece  the piece whose list is to be modified
 *  @param      sq120  120 based square involved in operation
 *  @param      operation  "add" or "del" to add square to pieceList or to remove it.
 *
 *  @return     Some error code if sq120 cant be deleted or cant be added. Else return success code (or some other useful info)
 * 
 *  
 *  
 *  @reminder   pieceList[x] is weirdly indexed to save space.
 *              for x = 0..4 => piece wP..wQ [ie piece 1..5]
 *              for x = 5..9 => piece bP..bQ [ie piece 7..11]
 *              piece EMPTY [piece 0] is not associated with any list
 *              piece wK or bK are associated with kingSq[] indexed by color.
**/
U8 S_BOARD::ModifySquareList(U8 piece, U8 sq120, std::string operation)
{
    if (operation == "add")
    {
        alt_pieceList[piece - 1].push_back(sq120);
    }

    else if (operation == "del")
    {
        alt_pieceList[piece - 1].erase(std::remove(alt_pieceList[piece - 1].begin(), alt_pieceList[piece - 1].end(), sq120), alt_pieceList[piece - 1].end());
    }
    return 0;
}


/** Prints PieceLists
 * 
 *  @param none
 *  @return none
**/
void S_BOARD::PrintPieceList()
{
    for (int i = 0; i < 12; i++)
    {
        printf("Piece[%d] : ", i + 1);

        for (U8 sq : alt_pieceList[i])
        {
             printf("%c%d ",SQ2FILE(sq) + 'A' - 1, SQ2RANK(sq));
        }
        printf("\n");
    }
}


/** Prints PieceLists (Alterenative)
 * 
 *  @param none
 *  @return none
**/
void S_BOARD::PrintPieceList2()
{
    for (int i = wP; i <= bK; i++)
    {
        printf("Piece[%d] : ", i);

        for (int j : GetSquareList(i))
        {
            printf("%c%d ",SQ2FILE(j) + 'A' - 1, SQ2RANK(j));   
        }
        printf("\n");
    }
}


/** Gets Side to Move
 * 
 *  @param  None
 *  @return U8 sideToMove. WHITE == 0, BLACK == 1
**/
U8 S_BOARD::GetSideToMove ()
{
    return this->sideToMove;
}


/** Gets En Passant Square
 * 
 *  @param  None
 *  @return U8 EP Square in 120 based indexing.
**/
U8 S_BOARD::GetEPSquare ()
{
    return this->enPassantSquare;
}


/** Gets Castling Rights
 * 
 *  @param  None
 *  @return U8 castleRights. Bitwise OR of available castle permissions.
**/
U8 S_BOARD::GetCastleRights ()
{
    return this->castleRights;
}
