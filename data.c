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

void UpdateListMaterial(S_BOARD *pos){
    int piece, sq, index, color;

    for(index = 0; index < BRD_SQ_NUM; ++index){
        sq = index;
        piece = pos->pieces[index];
        if(piece != OFFBOARD && piece != EMPTY){
            color = PieceCol[piece];
            
            if(PieceBig[piece] == TRUE) pos->bigPce[color]++;
            if(PieceMin[piece] == TRUE) pos->minPce[color]++;
            if(PieceMjr[piece] == TRUE) pos->mjrPce[color]++;

            pos->material[color] += PieceVal[piece];

            //Piece List
            pos->pList[piece][pos->pceNum[piece]] = sq;
            pos->pceNum[piece]++;

            if(piece == wK) pos->KingSq[WHITE] = sq;
            if(piece == bK) pos->KingSq[BLACK] = sq;
        }
    }
}