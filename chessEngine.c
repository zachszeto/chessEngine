#include "stdio.h"
#include "stdlib.h"
#include "defs.h"
/*
    #define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
    #define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
    #define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
*/

#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define FEN1 "8/3q4/8/8/4Q3/8/8/8 w - - 0 2 "

void ShowSqAtBySide(const int side, const S_BOARD *pos){
    int rank = 0;
    int file = 0;
    int sq = 0;

    printf("\n\nSquare attacked by:%c\n", SideChar[side]);
    for(rank = RANK_8; rank >= RANK_1; --rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            if(SqAttacked(sq, side, pos) == TRUE){
                printf("X");
            } else {
                printf("-");
            }
	    }
        printf("\n");
    }
    printf("\n");
}

int main() {
    AllInit();

    S_BOARD board[1];

    ParseFen(FEN1, board);
    UpdateListMaterial(board);
    PrintBoard(board);

    printf("\n\nWhite Attacking:\n");
    ShowSqAtBySide(WHITE, board);

    printf("\n\nBlack Attacking:\n");
    ShowSqAtBySide(BLACK, board);
    
    return 0;
}

    /*
        S_BOARD board[1];

        ParseFen(START_FEN, board);
        PrintBoard(board);

        ParseFen(FEN1, board);
        PrintBoard(board);

        ParseFen(FEN2, board);
        PrintBoard(board);

        ParseFen(FEN3, board);
        PrintBoard(board);
    */

    //Setting and Clearing Bit Test
    /*
        int index = 0;
        U64 playBitBoard = 0ULL;

        for(index = 0; index < 64; index++){
            printf("Index:%d\n", index);
            PrintBitBoard(ClearMask[index]);
            printf("\n");
        }

        SETBIT(playBitBoard, 61);
        PrintBitBoard(playBitBoard);

        CLRBIT(playBitBoard, 61);
        PrintBitBoard(playBitBoard);
    */

    //Bit Board POP() Test
    /*
            U64 playBitBoard = 0ULL;
            playBitBoard |= (1ULL << SQ64(D2));
            playBitBoard |= (1ULL << SQ64(D3));
            playBitBoard |= (1ULL << SQ64(D4));

            int sq64 = 0;

            while(playBitBoard){
                sq64 = POP(&playBitBoard);
                printf("Popped:%d\n", sq64);
                PrintBitBoard(playBitBoard);
            }
    */
    
    //64 and 120 Base Array Test
    /* 
        int index = 0;
        for(index = 0; index < BRD_SQ_NUM; ++index){
            if(index % 10 == 0) printf("\n");
            printf("%5d", Sq120ToSq64[index]);
        }

        printf("\n");   
        printf("\n");   
        for(index = 0; index < 64; ++index){
            if(index % 8 == 0) printf("\n");
            printf("%5d", Sq64ToSq120[index]);
        }
    */
    
   //Bit Board Test
    /*
        // Empty Bit Board
        U64 playBitBoard = 0ULL;
        printf("Start:\n\n");
        PrintBitBoard(playBitBoard);

        // Bit Board with pawn on D2
        playBitBoard |= (1ULL << SQ64(D2));
        printf("D2 Added:\n\n");
        PrintBitBoard(playBitBoard);

        // Bit Board with pawn on G2
        playBitBoard |= (1ULL << SQ64(G2));
        printf("G2 Added:\n\n");
        PrintBitBoard(playBitBoard);
    */