#include "header.h"

std::vector<S_MOVE> moveList;

void addQuietMove(Board& board, Move& move)       // Here means No Capture
{
    moveList.push_back(move);
}


void addCaptureMove(Board& board, Move& move)        // Here means No Capture
{
    moveList.push_back(move);
}

void RookListGenerator(Board& board, U8 piece)
{
    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        auto rookList = board.GetSquareList(piece);

        for(U8 rookSquare : rookList)
        {
            if(!SQLEGAL(rookSquare))
                continue;

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = rookSquare + i*10;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)//capture move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else{
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = rookSquare + i*10;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = rookSquare + i;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = rookSquare + i;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }
        }
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        auto rookList = board.GetSquareList(E_PIECE::bR);

        for(U8 rookSquare : rookList)
        {
            if(!SQLEGAL(rookSquare))
                continue;

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = rookSquare + i*10;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else{
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = rookSquare + i*10;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = rookSquare + i;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = rookSquare + i;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,rookSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
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

void BishopListGenerator(Board& board, U8 piece)
{

    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        auto bishopList = board.GetSquareList(piece);

        for(U8 bishopSquare : bishopList)
        {
            if(!SQLEGAL(bishopSquare))
                continue;

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = bishopSquare + i*11;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)//capture move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else{
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = bishopSquare + i*11;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = bishopSquare + i*9;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = bishopSquare + i*9;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK)
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }
        }
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        auto bishopList = board.GetSquareList(E_PIECE::bB);

        for(U8 bishopSquare : bishopList)
        {
            if(!SQLEGAL(bishopSquare))
                continue;

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = bishopSquare + i*11;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else{
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = bishopSquare + i*11;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = 1; i < 8; i++)
            {
                U8 toSquare = bishopSquare + i*9;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                    break;
                }

                else
                {
                    break;
                }
            }

            for(int i = -1; i > -8; i--)
            {
                U8 toSquare = bishopSquare + i*9;

                if(SQLEGAL(toSquare) && board.GetPieceOnSquare(toSquare) == E_PIECE::EMPTY)//silent move
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addQuietMove(board,move);
                }

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE)
                {
                    Move move(board,bishopSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
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

    if(board.GetSideToMove() == E_COLOR::WHITE)
    {
        auto knightList = board.GetSquareList(E_PIECE::wN);

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

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::BLACK) //capture move
                {
                    Move move(board,knightSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                }
            }
        }
    }

    else if(board.GetSideToMove() == E_COLOR::BLACK)
    {
        auto knightList = board.GetSquareList(E_PIECE::bN);

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

                else if(SQLEGAL(toSquare) && PIECECOLOR(board.GetPieceOnSquare(toSquare)) == E_COLOR::WHITE) //capture move
                {
                    Move move(board,knightSquare,toSquare,PACKMOVE(0,0,0,0,0,0));
                    addCaptureMove(board,move);
                }
            }
        }
    }
}

void BishopMoves(Board& board)
{
    BishopListGenerator(board, E_PIECE::wB);
}

void RookMoves(Board& board)
{
    RookListGenerator(board, E_PIECE::wR);
}

void QueenMoves(Board& board)
{
    RookListGenerator(board, E_PIECE::wQ);
    BishopListGenerator(board, E_PIECE::wQ);
}
