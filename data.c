#include "defs.h"

char PceChar[] = ".PNBRQKpnbrqk";
char SideChar[] = "wb-";
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";

int PieceBig[13] = {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};
int PieceMjr[13] = {FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE};
int PieceMin[13] = {FALSE, FALSE , TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE};
int PieceVal[13] = {0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000};
int PieceCol[13] = {BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

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
        }
    }
}