#include "defs.h"
#include "stdlib.h"

#define RAND_64 	((U64)rand() | \
					(U64)rand() << 15 | \
					(U64)rand() << 30 | \
					(U64)rand() << 45 | \
					((U64)rand() & 0xf) << 60 )

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

int FilesBRD[BRD_SQ_NUM];
int RanksBRD[BRD_SQ_NUM];

// Initialize the FilesBRD and RanksBRD arrays
void InitFilesRanksBRD(){

  // Index variable
  int index = 0; 
  
  // File and rank variables  
  int file = FILE_A;
  int rank = RANK_1;
  
  // Square index variable
  int sq = A1;
  
  // 64-bit square index variable  
  int sq64 = 0;

  // Loop through all board squares
  for(index = 0; index < BRD_SQ_NUM; ++index){
    
    // Set offboard value
    FilesBRD[index] = OFFBOARD;
    RanksBRD[index] = OFFBOARD;
  }

  // Loop through ranks
  for(rank = RANK_1; rank <= RANK_8; ++rank){

    // Loop through files
    for(file = FILE_A; file <= FILE_H; ++file){
    
      // Get square index
      sq = FR2SQ(file, rank);
      
      // Set file and rank for this square
      FilesBRD[sq] = file; 
      RanksBRD[sq] = rank;
    }
  }
}

// Initialize all hash keys used for zobrist hashing
void InitHashKeys() {
  int index = 0; 
  int index2 = 0;

  // Loop through all piece types
  for(index = 0; index < 13; ++index) {

    // Loop through all squares on board
    for(index2 = 0; index2 < 120; ++index2) {
    
      // Initialize random 64 bit hash key for this piece/square
      PieceKeys[index][index2] = RAND_64; 
    }
  }

  // Initialize random 64 bit hash key for side to move
  SideKey = RAND_64;

  // Loop through all possible castle rights permutations
  for(index = 0; index < 16; ++index) {

    // Initialize random 64 bit hash key for this set of castle rights
    CastleKeys[index] = RAND_64;
  }
}

// Initialize bit masks used for manipulating bitboards
void InitBitMasks() {
  int index = 0;

  // Loop through all squares on board
  for(index = 0; index < 64; index++) {

    // Initialize set mask and clear mask to 0
    SetMask[index] = 0ULL;
    ClearMask[index] = 0ULL;
  }

  // Loop through all squares again
  for(index = 0; index < 64; index++) {

    // Set indexth bit in set mask to 1, leaving others 0
    SetMask[index] |= (1ULL << index);
    
    // Invert set mask to create clear mask       
    ClearMask[index] = ~SetMask[index]; 
  }
}

// Initialize mappings between 64 bit and 120 bit square representations
void InitSq120To64() {
  int index = 0;
  int file = FILE_A; 
  int rank = RANK_1;
  int sq = A1;
  int sq64 = 0;

  // Set all 120-bit squares to invalid value
  for(index = 0; index < BRD_SQ_NUM; ++index) {
    Sq120ToSq64[index] = 65; // Invalid square
  }
  
  // Set all 64-bit squares to invalid value
  for(index = 0; index < 64; ++index) {
    Sq64ToSq120[index] = 120; // Invalid square
  }

  // Loop through all ranks and files
  for(rank = RANK_1; rank <= RANK_8; ++rank) {
    for(file = FILE_A; file <= FILE_H; ++file) {
      
      // Get 120-bit square index
      sq = FR2SQ(file, rank);
      
      // Set mappings between 64-bit and 120-bit squares
      Sq64ToSq120[sq64] = sq; 
      Sq120ToSq64[sq] = sq64;

      sq64++; 
    }
  }
}

void AllInit(){
     InitSq120To64();
     InitBitMasks();
     InitHashKeys();
     InitFilesRanksBRD();
}