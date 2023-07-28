#include "stdio.h"
#include "defs.h"

int main() {
    AllInit();
    return 0;
}

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