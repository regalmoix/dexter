#include "header.h"

std::vector<S_MOVE> moveList;

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

bool isAttacked(Board& board, U8 sq120)
{

    U8 side = board.GetSideToMove();
    int dir[4] = {-1,10,1,-10};
    for(int i = 0; i < 4; i++)
    {
        for(int j = 1; j < 8; j++)
        {
            U8 checkSquare = sq120 + dir[i]*j;
            if(SQLEGAL(checkSquare) && board.GetPieceOnSquare(checkSquare) == E_PIECE::EMPTY)
            {
                continue;
            }

            if(i == 1)
            {
                if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side
                && (isRook(board,checkSquare) || isQueen(board,checkSquare) || isKing(board,checkSquare)))
                {
                    return true;
                }
            }

            if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side
            && (isRook(board,checkSquare) || isQueen(board,checkSquare)))
            {
                return true;
            }

            else{
                break;
            }
        }
    }


    int dir2[4] = {9,11,-9,-11};
    for(int i = 0; i < 4; i++)
    {
        for(int j = 1; j < 8; j++)
        {
            U8 checkSquare = sq120 + dir2[i]*j;
            if(SQLEGAL(checkSquare) && board.GetPieceOnSquare(checkSquare) == E_PIECE::EMPTY)
            {
                continue;
            }

            if(i == 1)
            {
                if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side
                && (isBishop(board,checkSquare) || isQueen(board,checkSquare) || isKing(board,checkSquare)))
                {
                    return true;
                }
            }

            if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side
            && (isBishop(board,checkSquare) || isQueen(board,checkSquare)))
            {
                return true;
            }

            else{
                break;
            }
        }
    }

    //knight checking
    int dirx[8] = {-2,-1,1,2,2,1,-1,-2};
    int diry[8] = {1,2,2,1,-1,-2,-2,-1};
    for(int i = 0; i < 8; i++)
    {
        U8 checkSquare = sq120 + dirx[i] + diry[i]*10;
        if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && isKnight(board,checkSquare))
        {
            return true;
        }
    }

    // pawn checking
    int pawnDir[2] = {1,-1};
    for(int i = 0; i < 2; i++){

        int checkSquare = sq120 + i*11;
        if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && isPawn(board,checkSquare))
        {
            return true;
        }

        checkSquare = sq120 + i*9;
        if(SQLEGAL(checkSquare) && PIECECOLOR(board.GetPieceOnSquare(checkSquare)) != side && isPawn(board,checkSquare))
        {
            return true;
        }
    }


    return false;
}

void addQuietMove(Board& board, Move& move)       // Here means No Capture
{
    moveList.push_back(move);
}


void addCaptureMove(Board& board, Move& move)        // Here means No Capture
{
    moveList.push_back(move);
}

void PawnMoves(Board& board)
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
                        addQuietMove(board, move);
                    }
                }


                // Rank 7 -> 8 Capture Promotions
                if (SQLEGAL(pawnSquare + 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 9)) == E_COLOR::BLACK)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 9, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(board, move);
                    }
                }

                if (SQLEGAL(pawnSquare + 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 11)) == E_COLOR::BLACK)
                {
                    for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                    {
                        Move move(board, pawnSquare, pawnSquare + 11, PACKMOVE(0, 0, 0, 0, 1, x));
                        addCaptureMove(board, move);
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
                addQuietMove(board, move);
            }

            // Pawn not on Ranks 7 or 8, Double Push Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_2) && (board.GetPieceOnSquare(pawnSquare + 20) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(pawnSquare + 10) == E_PIECE::EMPTY))
            {
                Move move(board, pawnSquare, pawnSquare + 20, PACKMOVE(0,0,1,0,0,0));
                addQuietMove(board, move);
            }

            // Pawn not on Ranks 7 or 8, Capture Moves
            if (SQLEGAL(pawnSquare + 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 9)) == E_COLOR::BLACK)
            {
                    Move move(board, pawnSquare, pawnSquare + 9);
                    addCaptureMove(board, move);
            }

            if (SQLEGAL(pawnSquare + 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare + 11)) == E_COLOR::BLACK)
            {
                Move move(board, pawnSquare, pawnSquare + 11);
                addCaptureMove(board, move);
            }


            // Pawn on Rank 5, En Passant Move
            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_5) && SQLEGAL(pawnSquare + 9) && (board.GetEPSquare() == pawnSquare + 9))
            {
                Move move(board, pawnSquare, pawnSquare + 9, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(board, move);
            }

            if ((SQ2RANK(pawnSquare) == E_RANK::Rank_5) && SQLEGAL(pawnSquare + 11) && (board.GetEPSquare() == pawnSquare + 11))
            {
                Move move(board, pawnSquare, pawnSquare + 11, PACKMOVE(0,1,0,0,0,0));
                addCaptureMove(board, move);
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
                      addQuietMove(board, move);
                  }
              }


              // Rank 2 -> 1 Capture Promotions
              if (SQLEGAL(pawnSquare - 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 9)) == E_COLOR::WHITE)
              {
                  for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                  {
                      Move move(board, pawnSquare, pawnSquare - 9, PACKMOVE(0, 0, 0, 0, 1, x));
                      addCaptureMove(board, move);
                  }
              }

              if (SQLEGAL(pawnSquare - 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 11)) == E_COLOR::WHITE)
              {
                  for (int x = E_PROMPIECE::Prom_N; x <= E_PROMPIECE::Prom_Q; ++x)
                  {
                      Move move(board, pawnSquare, pawnSquare - 11, PACKMOVE(0, 0, 0, 0, 1, x));
                      addCaptureMove(board, move);
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
              addQuietMove(board, move);
          }

          // Pawn not on Ranks 7 or 8, Double Push Move
          if ((SQ2RANK(pawnSquare) == E_RANK::Rank_7) && (board.GetPieceOnSquare(pawnSquare - 20) == E_PIECE::EMPTY) && (board.GetPieceOnSquare(pawnSquare - 10) == E_PIECE::EMPTY))
          {
              Move move(board, pawnSquare, pawnSquare - 20, PACKMOVE(0,0,1,0,0,0));
              addQuietMove(board, move);
          }

          // Pawn not on Ranks 7 or 8, Capture Moves
          if (SQLEGAL(pawnSquare - 9) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 9)) == E_COLOR::WHITE)
          {
                  Move move(board, pawnSquare, pawnSquare - 9);
                  addCaptureMove(board, move);
          }

          if (SQLEGAL(pawnSquare - 11) && PIECECOLOR(board.GetPieceOnSquare(pawnSquare - 11)) == E_COLOR::WHITE)
          {
              Move move(board, pawnSquare, pawnSquare - 11);
              addCaptureMove(board, move);
          }


          // Pawn on Rank 5, En Passant Move
          if ((SQ2RANK(pawnSquare) == E_RANK::Rank_4) && SQLEGAL(pawnSquare - 9) && (board.GetEPSquare() == pawnSquare - 9))
          {
              Move move(board, pawnSquare, pawnSquare - 9, PACKMOVE(0,1,0,0,0,0));
              addCaptureMove(board, move);
          }

          if ((SQ2RANK(pawnSquare) == E_RANK::Rank_4) && SQLEGAL(pawnSquare - 11) && (board.GetEPSquare() == pawnSquare - 11))
          {
              Move move(board, pawnSquare, pawnSquare - 11, PACKMOVE(0,1,0,0,0,0));
              addCaptureMove(board, move);
          }
      }
    }
}

void KnightMoves(Board& board)
{
    int dirx[8] = {-2,-1,1,2,2,1,-1,-2};
    int diry[8] = {1,2,2,1,-1,-2,-2,-1};

    auto knightList = board.GetSquareList(E_PIECE::wN);
    if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        knightList = board.GetSquareList(E_PIECE::bN);
    }

    for(U8 knightSquare : knightList)
    {
        if(!SQLEGAL(knightSquare))
            continue;

        for(int i = 0; i < 8; i++)
        {

            U8 toSquare = knightSquare + dirx[i] + diry[i]*10;
            if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY) //silent move
            {
                Move move(board,knightSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                addQuietMove(board,move);
            }

            else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) != board.GetSideToMove()) //capture move
            {
                Move move(board,knightSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                addCaptureMove(board,move);
            }
        }
    }
}


void RookListGenerator(Board& board, U8 piece)
{
    int dir[4] = {-1,10,1,-10};
    auto rookList = board.GetSquareList(piece);

    for(U8 rookSquare : rookList)
    {
        if(!SQLEGAL(rookSquare))
            continue;

        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j < 8; j++)
            {
                U8 toSquare = rookSquare + dir[i]*j;
                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) != PIECECOLOR(piece))//capture move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else{
                    break;
                }
            }
        }
    }
}

void BishopListGenerator(Board& board, U8 piece)
{

    int dir[4] = {9,11,-11,-9};
    auto bishopList = board.GetSquareList(piece);

    for(U8 bishopSquare : bishopList)
    {
        if(!SQLEGAL(bishopSquare))
            continue;

        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j < 8; j++)
            {
                U8 toSquare = bishopSquare + dir[i]*j;
                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) != PIECECOLOR(piece))//capture move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else{
                    break;
                }
            }
        }
    }
}


void BishopMoves(Board& board)
{
    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        BishopListGenerator(board, E_PIECE::wB);
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        BishopListGenerator(board, E_PIECE::bB);
    }

}

void RookMoves(Board& board)
{
    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        RookListGenerator(board, E_PIECE::wR);
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        RookListGenerator(board, E_PIECE::bR);
    }
}

void QueenMoves(Board& board)
{
    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        BishopListGenerator(board, E_PIECE::wQ);
        RookListGenerator(board, E_PIECE::wQ);
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        BishopListGenerator(board, E_PIECE::bQ);
        RookListGenerator(board, E_PIECE::bQ);
    }
}
