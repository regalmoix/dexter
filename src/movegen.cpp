#include "header.h"

// std::vector<S_MOVE> moveList;


bool isRook(Board& board, U8 sq120)
{
    return (board.GetPieceOnSquare(sq120) == E_PIECE::wR) || (board.GetPieceOnSquare(sq120) == E_PIECE::bR);
}


bool isBishop(Board& board, U8 sq120)
{
    return (board.GetPieceOnSquare(sq120) == E_PIECE::wB) || (board.GetPieceOnSquare(sq120) == E_PIECE::bB);
}


bool isQueen(Board& board, U8 sq120)
{
    return (board.GetPieceOnSquare(sq120) == E_PIECE::wQ) || (board.GetPieceOnSquare(sq120) == E_PIECE::bQ);
}


bool isKing(Board& board, U8 sq120)
{
    return (board.GetPieceOnSquare(sq120) == E_PIECE::wK) || (board.GetPieceOnSquare(sq120) == E_PIECE::bK);
}


bool isKnight(Board& board, U8 sq120)
{
    return (board.GetPieceOnSquare(sq120) == E_PIECE::wN) || (board.GetPieceOnSquare(sq120) == E_PIECE::bN);
}


bool isPawn(Board& board, U8 sq120)
{
    return (board.GetPieceOnSquare(sq120) == E_PIECE::wP) || (board.GetPieceOnSquare(sq120) == E_PIECE::bP);
}


bool isAttacked(Board& board, U8 sq120, S8 attackingside)
{
    assert(SQLEGAL(sq120));
    // 
    // printf("Entered  here  \n");
    // printf("%d\n",sq120);
    // fflush(stdout);

    S8 side;

    if (attackingside == -1)
        side = board.GetSideToMove();

    else
        side = (attackingside == E_COLOR::WHITE) ? E_COLOR::BLACK : E_COLOR::WHITE;                  // Because side is the defending side
         
    S8 dir[4] = {-1, 10, 1, -10};
    
    
    for (S8 i = 0; i < 4; i++)
    {
        for(S8 j = 1; j < 8; j++)
        {
            S8 checkSquare = sq120 + dir[i] * j;

            if (SQLEGAL(checkSquare) && board.GetPieceOnSquare(checkSquare) == E_PIECE::EMPTY)
                continue;

            if (j == 1)
            {
                if (SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && 
                   (isRook(board,checkSquare) || isQueen(board,checkSquare) || isKing(board,checkSquare)))
                {
                    // printf("yo1\n");
                    return true;
                }
            }

            if (SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && 
               (isRook(board,checkSquare) || isQueen(board,checkSquare)))
            {
                // printf("yo2\n");
                return true;
            }

            else
                break;
            
        }
    }


    S8 dir2[4] = {9, 11, -9, -11};

    for (S8 i = 0; i < 4; i++)
    {
        for (S8 j = 1; j < 8; j++)
        {
            S8 checkSquare = sq120 + dir2[i] * j;

            if(SQLEGAL(checkSquare) && board.GetPieceOnSquare(checkSquare) == E_PIECE::EMPTY)
                continue;
            
            if(j == 1)
            {
                if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && 
                  (isBishop(board,checkSquare) || isQueen(board,checkSquare) || isKing(board,checkSquare)))
                {
                    // printf("yo3\n");
                    return true;
                }
            }

            if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side
            && (isBishop(board,checkSquare) || isQueen(board,checkSquare)))
            {
                // printf("yo4\n");
                return true;
            }

            else
                break;
        }
    }

    //knight checking
    S8 dirx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    S8 diry[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (S8 i = 0; i < 8; i++)
    {
        S8 checkSquare = sq120 + dirx[i] + diry[i] * 10;

        if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && isKnight(board,checkSquare))
        {
            // printf("yo5\n");
            return true;
        }
    }

    // pawn checking
    S8 pawnDir[2] = {9, 11};
    for(S8 i = 0; i < 2; i++)
    {
        int checkSquare;
        if(side==E_COLOR::WHITE){
            checkSquare = sq120 + pawnDir[i];
        }

        else{
            checkSquare = sq120 - pawnDir[i];
        }

        if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && isPawn(board,checkSquare))
        {
            // printf("yo6\n");
            return true;
        }

        // checkSquare = sq120 + i * 9;

        // if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && isPawn(board,checkSquare))
        // {
        //     printf("yo7\n");
        //     return true;
        // }
    }
    return false;
}


void addQuietMove(Move& move, std::vector<S_MOVE>& moveList)       // Here means No Capture
{
    moveList.push_back(move);
}


void addCaptureMove(Move& move, std::vector<S_MOVE>& moveList)
{
    moveList.push_back(move);
}


void PawnMoves(Board& board, std::vector<S_MOVE>& moveList)
{
    if (board.GetSideToMove() == E_COLOR::WHITE)
    {
        auto pawnSqList = board.GetSquareList(E_PIECE::wP);

        for (U8 pawnSquare : pawnSqList)
        {
            // cout << (int)pawnSquare  << endl;
            //assert (pawnSquare != E_SQUARE::Square_Invalid);
            if (pawnSquare == E_SQUARE::Square_Invalid)
                continue;

            assert (SQ2RANK(pawnSquare) != E_RANK::Rank_8);

            if (SQ2RANK(pawnSquare) == E_RANK::Rank_7)  // These can not be quiet moves
            {
                // Rank 7 -> 8 Quiet Promotion
                if (board.GetPieceOnSquare(pawnSquare + 10) == E_PIECE::EMPTY)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 10, PACKMOVE(0, 0, 0, 0, 1, x));
                        addQuietMove(move, moveList);
                    }
                }


                // Rank 7 -> 8 Capture Promotions
                if (SQLEGAL(pawnSquare + 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 9)) == E_COLOR::BLACK)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 9, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(move, moveList);
                    }
                }

                if (SQLEGAL(pawnSquare + 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 11)) == E_COLOR::BLACK)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 11, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(move, moveList);
                    }
                }
                continue;
            }

            // Pawn not on Ranks 7 or 8, Quiet Move
            // cout << (int)pawnSquare << endl;
            if (board.GetPieceOnSquare(pawnSquare + 10) == E_PIECE::EMPTY)
            {
                //cout << "Test";
                Move move(board, pawnSquare, pawnSquare + 10);
                addQuietMove(move, moveList);
            }

            // Pawn not on Ranks 7 or 8, Double Push Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_2) && (board.GetPieceOnSquare(pawnSquare + 20) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(pawnSquare + 10) == E_PIECE::EMPTY))
            {
                Move move(board, pawnSquare, pawnSquare + 20, PACKMOVE(0,0,1,0,0,0));
                addQuietMove(move, moveList);
            }

            // Pawn not on Ranks 7 or 8, Capture Moves
            if (SQLEGAL(pawnSquare + 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 9)) == E_COLOR::BLACK)
            {
                    Move move(board, pawnSquare, pawnSquare + 9);
                    addCaptureMove(move, moveList);
            }

            if (SQLEGAL(pawnSquare + 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 11)) == E_COLOR::BLACK)
            {
                Move move(board, pawnSquare, pawnSquare + 11);
                addCaptureMove(move, moveList);
            }


            // Pawn on Rank 5, En Passant Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_5) && SQLEGAL(pawnSquare + 9) && (board.GetEPSquare() == pawnSquare + 9))
            {
                Move move(board, pawnSquare, pawnSquare + 9, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(move, moveList);
            }

            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_5) && SQLEGAL(pawnSquare + 11) && (board.GetEPSquare() == pawnSquare + 11))
            {
                Move move(board, pawnSquare, pawnSquare + 11, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(move, moveList);
            }
        }
    }

    else if (board.GetSideToMove() == E_COLOR::BLACK)
    {
        auto pawnSqList = board.GetSquareList(E_PIECE::bP);

        for (U8 pawnSquare : pawnSqList)
        {
            // cout << (int)pawnSquare  << endl;
            //assert (pawnSquare != E_SQUARE::Square_Invalid);
            if (pawnSquare == E_SQUARE::Square_Invalid)
                continue;

            assert (SQ2RANK(pawnSquare) != E_RANK::Rank_1);

            if (SQ2RANK(pawnSquare) == E_RANK::Rank_2)  // These can not be quiet moves
            {
                // Rank 2 -> 1 Quiet Promotion
                if (board.GetPieceOnSquare(pawnSquare - 10) == E_PIECE::EMPTY)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare - 10, PACKMOVE(0, 0, 0, 0, 1, x));
                        addQuietMove(move, moveList);
                    }
                }


                // Rank 2 -> 1 Capture Promotions
                if (SQLEGAL(pawnSquare - 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 9)) == E_COLOR::WHITE)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare - 9, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(move, moveList);
                    }
                }

                if (SQLEGAL(pawnSquare - 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 11)) == E_COLOR::WHITE)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare - 11, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(move, moveList);
                    }
                }
                continue;
            }

            // Pawn not on Ranks 7 or 8, Quiet Move
            // cout << (int)pawnSquare << endl;
            if (board.GetPieceOnSquare(pawnSquare - 10) == E_PIECE::EMPTY)
            {
                //cout << "Test";
                Move move(board, pawnSquare, pawnSquare - 10);
                addQuietMove(move, moveList);
            }

            // Pawn not on Ranks 7 or 8, Double Push Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_7) && (board.GetPieceOnSquare(pawnSquare - 20) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(pawnSquare - 10) == E_PIECE::EMPTY))
            {
                Move move(board, pawnSquare, pawnSquare - 20, PACKMOVE(0,0,1,0,0,0));
                addQuietMove(move, moveList);
            }

            // Pawn not on Ranks 7 or 8, Capture Moves
            if (SQLEGAL(pawnSquare - 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 9)) == E_COLOR::WHITE)
            {
                Move move(board, pawnSquare, pawnSquare - 9);
                addCaptureMove(move, moveList);
            }

            if (SQLEGAL(pawnSquare - 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 11)) == E_COLOR::WHITE)
            {
                Move move(board, pawnSquare, pawnSquare - 11);
                addCaptureMove(move, moveList);
            }


            // Pawn on Rank 5, En Passant Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_4) && SQLEGAL(pawnSquare - 9) && (board.GetEPSquare() == pawnSquare - 9))
            {
                Move move(board, pawnSquare, pawnSquare - 9, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(move, moveList);
            }

            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_4) && SQLEGAL(pawnSquare - 11) && (board.GetEPSquare() == pawnSquare - 11))
            {
                Move move(board, pawnSquare, pawnSquare - 11, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(move, moveList);
            }
      }
    }
}


void KnightMoves(Board& board, std::vector<S_MOVE>& moveList)
{
    S8 dirx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    S8 diry[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    auto knightList = board.GetSquareList(E_PIECE::wN);

    if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        knightList = board.GetSquareList(E_PIECE::bN);
    }

    for(U8 knightSquare : knightList)
    {
        if(!SQLEGAL(knightSquare))
            continue;

        for(U8 i = 0; i < 8; i++)
        {

            U8 toSquare = knightSquare + dirx[i] + diry[i] * 10;
            if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY) //silent move
            {
                Move move(board,knightSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                addQuietMove(move, moveList);
            }

            else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) != board.GetSideToMove()) //capture move
            {
                Move move(board,knightSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                addCaptureMove(move, moveList);
            }
        }
    }
}


void RookListGenerator(Board& board, U8 piece, std::vector<S_MOVE>& moveList)
{
    S8 dir[4] = {-1, 10, 1, -10};
    auto rookList = board.GetSquareList(piece);

    for(U8 rookSquare : rookList)
    {
        if(!SQLEGAL(rookSquare))
            continue;

        for(U8 i = 0; i < 4; i++)
        {
            for(U8 j = 1; j < 8; j++)
            {
                U8 toSquare = rookSquare + dir[i]*j;
                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(move, moveList);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) != PIECECOLOR(piece))//capture move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(move, moveList);
                    break;
                }

                else
                {
                    break;
                }
            }
        }
    }
}


void BishopListGenerator(Board& board, U8 piece, std::vector<S_MOVE>& moveList)
{
    S8 dir[4] = {9, 11, -11, -9};

    auto bishopList = board.GetSquareList(piece);

    for (U8 bishopSquare : bishopList)
    {
        if(!SQLEGAL(bishopSquare))
            continue;

        for(U8 i = 0; i < 4; i++)
        {
            for(U8 j = 1; j < 8; j++)
            {
                U8 toSquare = bishopSquare + dir[i]*j;
                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(move, moveList);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) != PIECECOLOR(piece))//capture move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(move, moveList);
                    break;
                }

                else
                    break;
            }
        }
    }
}


void BishopMoves(Board& board, std::vector<S_MOVE>& moveList)
{
    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        BishopListGenerator(board, E_PIECE::wB, moveList);
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        BishopListGenerator(board, E_PIECE::bB, moveList);
    }

}


void RookMoves(Board& board, std::vector<S_MOVE>& moveList)
{
    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        RookListGenerator(board, E_PIECE::wR, moveList);
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        RookListGenerator(board, E_PIECE::bR, moveList);
    }
}


void QueenMoves(Board& board, std::vector<S_MOVE>& moveList)
{
    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        BishopListGenerator(board, E_PIECE::wQ, moveList);
        RookListGenerator(board, E_PIECE::wQ, moveList);
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        BishopListGenerator(board, E_PIECE::bQ, moveList);
        RookListGenerator(board, E_PIECE::bQ, moveList);
    }
}


void KingMoves(Board& board, std::vector<S_MOVE>& moveList)
{
    S8 dir[8] = {-1, 10, 1, -10, 9, 11, -11, -9};

    U8 side = board.GetSideToMove();
    assert (side == E_COLOR::WHITE || side == E_COLOR::BLACK);

    U8 pce  = ((side == E_COLOR::WHITE) ? E_PIECE::wK : E_PIECE::bK);

    std::vector<U8> kingList = board.GetSquareList(pce);
    
    U8 kingSq = E_SQUARE::Square_Invalid;

    // NOTE : when the GetSquareList function updated to return valid squares, we can safely replace below loop with kingSq = kingList[0]
    for (U8 sq : kingList)
    {
        if (SQLEGAL(sq))
        {
            kingSq = sq;
            break;
        }
    }
    
    // for (int i = 0; i < 120; i++)
    // {
    //     if (board.GetPieceOnSquare(i) == pce)
    //     {
    //         kingSq = i;
    //         break;
    //     }
    // }

    assert(SQLEGAL(kingSq));



    for (S8 d : dir)
    {
        U8 toSquare = kingSq + d;
        if (SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY) //silent move
        {
            Move move(board, kingSq, toSquare, PACKMOVE(0,0,0,0,0,0));
            addQuietMove(move, moveList);
        }

        else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) != PIECECOLOR(pce)) //capture move
        {
            Move move(board, kingSq, toSquare, PACKMOVE(0,0,0,0,0,0));
            addCaptureMove(move, moveList);
        }
    }

    // Castle moves
    if (side == E_COLOR::WHITE && kingSq == E_SQUARE::E1)
    {
        if (board.GetCastleRights() & E_CASTLE_RIGHTS::wK_castle)
        {
            if ((board.GetPieceOnSquare(E_SQUARE::F1) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(E_SQUARE::G1) == E_PIECE::EMPTY))
            {
                if (!isAttacked(board, E_SQUARE::E1) && !isAttacked(board, E_SQUARE::F1) && !isAttacked(board, E_SQUARE::G1))
                {
                    Move move(board, E_SQUARE::E1, E_SQUARE::G1, PACKMOVE(0,0,0,2,0,0));
                    addQuietMove(move, moveList);
                }
            }
        }

        if (board.GetCastleRights() & E_CASTLE_RIGHTS::wQ_castle)
        {          
            if ((board.GetPieceOnSquare(E_SQUARE::D1) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(E_SQUARE::B1) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(E_SQUARE::C1) == E_PIECE::EMPTY))
            {
                if (!isAttacked(board, E_SQUARE::E1) && !isAttacked(board, E_SQUARE::D1) && !isAttacked(board, E_SQUARE::C1))
                {
                    Move move(board, E_SQUARE::E1, E_SQUARE::C1, PACKMOVE(0,0,0,3,0,0));
                    addQuietMove(move, moveList);
                }
            }
        }
    }

    else if (side == E_COLOR::BLACK && kingSq == E_SQUARE::E8)
    {
        if (board.GetCastleRights() & E_CASTLE_RIGHTS::bK_castle)
        {
            if ((board.GetPieceOnSquare(E_SQUARE::F8) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(E_SQUARE::G8) == E_PIECE::EMPTY))
            {
                if (!isAttacked(board, E_SQUARE::E8) && !isAttacked(board, E_SQUARE::F8) && !isAttacked(board, E_SQUARE::G8))
                {
                    Move move(board, E_SQUARE::E8, E_SQUARE::G8, PACKMOVE(0,0,0,2,0,0));
                    addQuietMove(move, moveList);
                }
            }           
        }

        if (board.GetCastleRights() & E_CASTLE_RIGHTS::bQ_castle)
        {
            if ((board.GetPieceOnSquare(E_SQUARE::D8) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(E_SQUARE::B8) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(E_SQUARE::C8) == E_PIECE::EMPTY))
            {
                if (!isAttacked(board, E_SQUARE::E8) && !isAttacked(board, E_SQUARE::D8) && !isAttacked(board, E_SQUARE::C8))
                {
                    Move move(board, E_SQUARE::E8, E_SQUARE::C8, PACKMOVE(0,0,0,3,0,0));
                    addQuietMove(move, moveList);
                }
            }
        }
    }
    
}


void AllMoves (Board& board, std::vector<S_MOVE>& moveList)
{
    PawnMoves(board, moveList);
    for (auto m : moveList)
        assert(SQLEGAL(m.fromSquare) && SQLEGAL(m.fromSquare));

    KnightMoves(board, moveList);
    for (auto m : moveList)
        assert(SQLEGAL(m.fromSquare) && SQLEGAL(m.fromSquare));
       
    BishopMoves(board, moveList);
    for (auto m : moveList)
        assert(SQLEGAL(m.fromSquare) && SQLEGAL(m.fromSquare));
       
    RookMoves(board, moveList);
    for (auto m : moveList)
        assert(SQLEGAL(m.fromSquare) && SQLEGAL(m.fromSquare));
       
    QueenMoves(board, moveList);
    for (auto m : moveList)
        assert(SQLEGAL(m.fromSquare) && SQLEGAL(m.fromSquare));
       
    KingMoves(board, moveList);
    for (auto m : moveList)
        assert(SQLEGAL(m.fromSquare) && SQLEGAL(m.fromSquare));
       
}