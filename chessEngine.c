#include "stdio.h"
#include "defs.h"

int main() {

    AllInit();

    U64 playBitBoard = 0ULL;
    playBitBoard |= (1ULL << SQ64(D2));
    playBitBoard |= (1ULL << SQ64(D3));
    playBitBoard |= (1ULL << SQ64(D4));

    printf("\n");
    PrintBitBoard(playBitBoard);

    int count = CNT(playBitBoard);
    printf("Count: %d\n", count);

    int index = POP(&playBitBoard);
    printf("Index: %d\n", index);

    PrintBitBoard(playBitBoard);
    count = CNT(playBitBoard);
    printf("Count: %d\n", count);
    
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
    return 0;
}