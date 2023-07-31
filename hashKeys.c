#include "stdio.h"
#include "defs.h"

// Generate a 64 bit position key from the position information
U64 GeneratePosKey(const S_BOARD *pos) {

  int sq = 0; 
  U64 finalKey = 0;
  int piece = EMPTY;

  // loop through all squares on the board
  for(sq = 0; sq < BRD_SQ_NUM; ++sq) {
    
    // get the piece on the current square
    piece = pos->pieces[sq];
    
    // if there is a piece on the square (not empty or offboard)
    if(piece!=NO_SQ && piece!=EMPTY && piece != OFFBOARD) {

      // make sure piece is valid
      ASSERT(piece>=wP && piece<=bK); 
      
      // xor the piece key
      finalKey ^= PieceKeys[piece][sq]; 
    }
  }

  // xor side key if side to move is white
  if(pos->side == WHITE) {
    finalKey ^= SideKey; 
  }

  // xor en passant key if en passant square is set
  if(pos->enPas != NO_SQ) {
    ASSERT(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
    finalKey ^= PieceKeys[EMPTY][pos->enPas];
  }

  // xor castle keys based on castle permissions
  ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);
  finalKey ^= CastleKeys[pos->castlePerm];

  return finalKey;
}