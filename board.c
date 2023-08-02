#include "stdio.h"
#include "defs.h"

int CheckBoard(const S_BOARD *pos) {

	int t_pceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int t_bigPce[2] = { 0, 0};
	int t_mjrPce[2] = { 0, 0};
	int t_minPce[2] = { 0, 0};
	int t_material[2] = { 0, 0};

	int sq64,t_piece,t_pce_num,sq120,colour,pcount;

	U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

	t_pawns[WHITE] = pos->pawns[WHITE];
	t_pawns[BLACK] = pos->pawns[BLACK];
	t_pawns[BOTH] = pos->pawns[BOTH];

	// check piece lists
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		for(t_pce_num = 0; t_pce_num < pos->pceNum[t_piece]; ++t_pce_num) {
			sq120 = pos->pList[t_piece][t_pce_num];
			ASSERT(pos->pieces[sq120]==t_piece);
		}
	}

	// check piece count and other counters
	for(sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = SQ120(sq64);
		t_piece = pos->pieces[sq120];
		t_pceNum[t_piece]++;
		colour = PieceCol[t_piece];
		if( PieceBig[t_piece] == TRUE) t_bigPce[colour]++;
		if( PieceMin[t_piece] == TRUE) t_minPce[colour]++;
		if( PieceMjr[t_piece] == TRUE) t_mjrPce[colour]++;

		t_material[colour] += PieceVal[t_piece];
	}

	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		ASSERT(t_pceNum[t_piece]==pos->pceNum[t_piece]);
	}

	// check bitboards count
	pcount = CNT(t_pawns[WHITE]);
	ASSERT(pcount == pos->pceNum[wP]);
	pcount = CNT(t_pawns[BLACK]);
	ASSERT(pcount == pos->pceNum[bP]);
	pcount = CNT(t_pawns[BOTH]);
	ASSERT(pcount == (pos->pceNum[bP] + pos->pceNum[wP]));

	// check bitboards squares
	while(t_pawns[WHITE]) {
		sq64 = POP(&t_pawns[WHITE]);
		ASSERT(pos->pieces[SQ120(sq64)] == wP);
	}

	while(t_pawns[BLACK]) {
		sq64 = POP(&t_pawns[BLACK]);
		ASSERT(pos->pieces[SQ120(sq64)] == bP);
	}

	while(t_pawns[BOTH]) {
		sq64 = POP(&t_pawns[BOTH]);
		ASSERT( (pos->pieces[SQ120(sq64)] == bP) || (pos->pieces[SQ120(sq64)] == wP) );
	}

	ASSERT(t_material[WHITE]==pos->material[WHITE] && t_material[BLACK]==pos->material[BLACK]);
	ASSERT(t_minPce[WHITE]==pos->minPce[WHITE] && t_minPce[BLACK]==pos->minPce[BLACK]);
	ASSERT(t_mjrPce[WHITE]==pos->mjrPce[WHITE] && t_mjrPce[BLACK]==pos->mjrPce[BLACK]);
	ASSERT(t_bigPce[WHITE]==pos->bigPce[WHITE] && t_bigPce[BLACK]==pos->bigPce[BLACK]);

	ASSERT(pos->side==WHITE || pos->side==BLACK);
	ASSERT(GeneratePosKey(pos)==pos->posKey);

	ASSERT(pos->enPas==NO_SQ || (RanksBRD[pos->enPas] == RANK_6 && pos->side == WHITE) || (RanksBRD[pos->enPas] == RANK_3 && pos->side == BLACK));
		 

	ASSERT(pos->pieces[pos->KingSq[WHITE]] == wK);
	ASSERT(pos->pieces[pos->KingSq[BLACK]] == bK);

	ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);


	return TRUE;
}

// Update material count and piece lists for position
void UpdateListMaterial(S_BOARD *pos){
    int piece, sq, index, color;

    // Loop through all squares on board
    for(index = 0; index < BRD_SQ_NUM; ++index){
        
        sq = index; // Current square
        
        piece = pos->pieces[index]; // Get piece on current square
        
        if(piece != OFFBOARD && piece != EMPTY){
            
            // Get color of piece
            color = PieceCol[piece]; 
            
            // Update material counts
            if(PieceBig[piece] == TRUE) pos->bigPce[color]++; 
            if(PieceMin[piece] == TRUE) pos->minPce[color]++;
            if(PieceMjr[piece] == TRUE) pos->mjrPce[color]++;
    
            pos->material[color] += PieceVal[piece];
            
            // Update piece lists
            pos->pList[piece][pos->pceNum[piece]] = sq; 
            pos->pceNum[piece]++;
 
            // Update king square 
            if(piece == wK) pos->KingSq[WHITE] = sq;
            if(piece == bK) pos->KingSq[BLACK] = sq;

            if(piece==wP) {
				      SETBIT(pos->pawns[WHITE],SQ64(sq));
				      SETBIT(pos->pawns[BOTH],SQ64(sq));
			      } else if(piece==bP) {
				      SETBIT(pos->pawns[BLACK],SQ64(sq));
				      SETBIT(pos->pawns[BOTH],SQ64(sq));
			      }
        }
    }
}

// Parse FEN string into position structure
int ParseFen(char *fen, S_BOARD *pos) {

  // Validate input
	ASSERT(fen!=NULL);
	ASSERT(pos!=NULL);

   // Initialize ranks, files, and pieces
	int  rank = RANK_8;
  int  file = FILE_A;
  int  piece = 0;
  
  // Other helpers
  int  count = 0;
  int  i = 0;
	int  sq64 = 0;
	int  sq120 = 0;

  // Clear board
	ResetBoard(pos);

   // Parse ranks and files
	while ((rank >= RANK_1) && *fen) {
	  
    // Count empty squares
    count = 1;
		
     // Identify piece
    switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

             // Empty square count
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

            // Handle end of rank or errors
            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return -1;
        }

     // Add pieces to board
		for (i = 0; i < count; i++) {
            sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
			file++;
        }
		fen++;
	}

  // Side to move
	ASSERT(*fen == 'w' || *fen == 'b');

	pos->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;

   // Castling rights
	for (i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
		switch(*fen) {
			case 'K': pos->castlePerm |= WKCA; break;
			case 'Q': pos->castlePerm |= WQCA; break;
			case 'k': pos->castlePerm |= BKCA; break;
			case 'q': pos->castlePerm |= BQCA; break;
			default:	     break;
        }
		fen++;
	}
	fen++;

	ASSERT(pos->castlePerm>=0 && pos->castlePerm <= 15);

   // En passant square
	if (*fen != '-') {
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ASSERT(file>=FILE_A && file <= FILE_H);
		ASSERT(rank>=RANK_1 && rank <= RANK_8);

		pos->enPas = FR2SQ(file,rank);
    }

  // Generate position key
	pos->posKey = GeneratePosKey(pos);

	return 0;
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

void PrintBoard(const S_BOARD *pos) {

	int sq,file,rank,piece;

	printf("\nGame Board:\n\n");

	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; file++) {
			sq = FR2SQ(file,rank);
			piece = pos->pieces[sq];
			printf("%3c",PceChar[piece]);
		}
		printf("\n");
	}

	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; file++) {
		printf("%3c",'a'+file);
	}
	printf("\n");
	printf("side:%c\n",SideChar[pos->side]);
	printf("enPas:%d\n",pos->enPas);
	printf("castle:%c%c%c%c\n",
			pos->castlePerm & WKCA ? 'K' : '-',
			pos->castlePerm & WQCA ? 'Q' : '-',
			pos->castlePerm & BKCA ? 'k' : '-',
			pos->castlePerm & BQCA ? 'q' : '-'
			);
	printf("PosKey:%llX\n",pos->posKey);
}