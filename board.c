#include "stdio.h"
#include "defs.h"

int Parse_Fen(char *fen, S_BOARD *pos){
  //Making sure we are pointing at something
  ASSERT(fen!=NULL);
  ASSERT(pos!=NULL);

  int rank = RANK_8;
  int file = FILE_A;
  int piece = 0;
  int count = 0;
  int i = 0;
  int sq64 = 0;
  int sq120 = 0;

  ResetBoard(pos);

  while((rank >= RANK_1) && *fen){
    count = 1;
    switch (*fen){
      //Black Pieces
      case 'p': piece = bP; break;
      case 'r': piece = bR; break;
      case 'n': piece = bN; break;
      case 'b': piece = bB; break;
      case 'k': piece = bK; break;
      case 'q': piece = bQ; break;
      //White Pieces
      case 'P': piece = wP; break;
      case 'R': piece = wR; break;
      case 'N': piece = wN; break;
      case 'B': piece = wB; break;
      case 'K': piece = wK; break;
      case 'Q': piece = wQ; break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        piece = EMPTY;
        count = *fen - '0';
        break;
      
      case '/':
      case ' ':
        rank--;
        file = FILE_A;
        fen++;
        continue;

        default:
          printf("FEN ERROR \n");
          return -1;
    }

    for(i = 0; i < count; i++){
      sq64 = rank * 8 + file;
      sq120 = SQ120(sq64);
      if(piece != EMPTY){
        pos->pieces[sq120] = piece;
      }
      file++;
    }
    fen++;
  }
}

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