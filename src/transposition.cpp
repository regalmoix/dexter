#include "header.h"

S_TP_TABLE::S_TT_Entry::S_TT_Entry() : 
                    hashKey(0), score(0), depth(0), flag(FLAG_INVALID_ENTRY), ancient(true), move(Move::Invalid_Move)
{

}


S_TP_TABLE::S_TT_Entry::S_TT_Entry (U64 hashKey, Move move, S16 score, U8 depth, U8 flag) : 
                    hashKey(hashKey), score(score), depth(depth), flag(flag), ancient(false), move(move)
{
    // TODO : if score is near a Mate Score, i.e. |score| > MATE then set score to Mate and while probing, subtract depth accordingly
} 


S_TP_TABLE::S_TP_TABLE()
{
    hashHits                    = 0;
}


void S_TP_TABLE::StoreEntry (Board& board, Move& bestMove, S16 score,  U8 depth, U8 flag)
{
    U32 idx         = board.posHashKey % TP_SIZE; 
    TT_Entry entry  (board.posHashKey, bestMove, score, depth, flag);

    // Directly Overwrite the entry. Later we can use ancient flag or replace by depth
    // http://mediocrechess.blogspot.com/2007/01/guide-transposition-tables.html
    tp_table[idx]   = entry;
}


bool S_TP_TABLE::ProbeEntry (Board& board, Move& pvMove, S16& score, S16 alpha, S16 beta, U8 currDepth)
{
    U32 idx         = board.posHashKey % TP_SIZE; 

    // Verify position in the hash table same as our position
    if (board.posHashKey == tp_table[idx].hashKey)
    {
        //  Best Move in this position according to a previous Search
        pvMove = tp_table[idx].move;

        // If we are currently searching this position for shallower depth than we did before
        if (currDepth <= tp_table[idx].depth)
        {
            hashHits ++;
            score = tp_table[idx].score;

            switch (tp_table[idx].flag)
            {
                case FLAG_ALPHA : 
                {
                    if (score <= alpha) 
                    {
                        score = alpha; 
                        return true;
                    }
                    
                    break;
                }

                case FLAG_BETA :
                {
                    if (score >= beta) 
                    {
                        score = beta; 
                        return true;
                    }
                    
                    break;
                }
                
                case FLAG_EXACT : // No Change, we set score above
                {
                    return true;
                    break;
                }

                default :
                {
                    return false;
                    break;
                }
            }
        }   

    }

    return false;
}