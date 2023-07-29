#include "defs.h"
#include <stdio.h>

// Generate a 64 bit position key from the position information
U64 GeneratePosKey(const S_BOARD *pos) {

  int sq = 0; // square index
  U64 finalKey = 0; // final key to return
  int piece = EMPTY; // piece on square
  
  // Loop through all squares on the board
  for (sq = 0; sq < BRD_SQ_NUM; ++sq) {
    
    // Get piece on current square
    piece = pos->pieces[sq]; 
    
    // If square not empty or off board, update final key
    if (piece != NO_SQ && piece != EMPTY) {
      
      ASSERT(piece >= wP && piece <= bK); // Validate piece type
      
      // XOR piece key for current square
      finalKey ^= PieceKeys[piece][sq]; 
    }
  }
  
  // If side to move is white, XOR in white side key
  if (pos->side == WHITE) {
    finalKey ^= SideKey; 
  }
  
  // If en passant square is set, XOR in key for that square
  if (pos->enPas != NO_SQ) {  
    ASSERT(pos->enPas >= 0 && pos->enPas < BRD_SQ_NUM);
    finalKey ^= PieceKeys[EMPTY][pos->enPas];
  }

  // XOR in key for current castle permissions  
  ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);
  finalKey ^= CastleKeys[pos->castlePerm];

  return finalKey;
}