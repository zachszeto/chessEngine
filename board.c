#include "stdio.h"
#include "defs.h"

// Reset the board to the initial starting position
void ResetBoard(S_BOARD *pos) {
  int index = 0;

  // Set all squares to offboard
  for(index = 0; index < BRD_SQ_NUM; ++index) {
    pos->pieces[index] = OFFBOARD;
  }

  // Set squares on the board to empty
  for(index = 0; index < 64; ++index) {
    pos->pieces[SQ120(index)] = EMPTY;
  }

  // Clear piece bitboards
  for(index = 0; index < 3; ++index) {
    pos->bigPce[index] = 0;
    pos->mjrPce[index] = 0;
    pos->minPce[index] = 0;
    pos->pawns[index] = 0ULL; 
  }

  // Set piece counts to 0
  for(index = 0; index < 13; ++index) {
    pos->pceNum[index] = 0;
  }

  // Reset king squares
  pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

  // Reset side to move
  pos->side = BOTH; 

  // Clear en passant, fifty move, and ply counts
  pos->enPas = NO_SQ;
  pos->fiftyMove = 0;
  pos->ply = 0;
  pos->hisPly = 0;

  // Reset castle perms and pos key
  pos->castlePerm = 0;
  pos->posKey = 0ULL;
}