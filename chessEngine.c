#include "stdio.h"
#include "defs.h"

int main() {

    AllInit();
    
    //Prints out 64 base and 120 base arrays
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
    
    //Empty Bit Board
    U64 playBitBoard = 0ULL;
    printf("Start:\n\n");
    PrintBitBoard(playBitBoard);

    //Bit Board with pawn on D2
    playBitBoard |= (1ULL << SQ64(D2));
    printf("D2 Added:\n\n");
    PrintBitBoard(playBitBoard);

    //Bit Board with pawn on G2
    playBitBoard |= (1ULL << SQ64(G2));
    printf("G2 Added:\n\n");
    PrintBitBoard(playBitBoard);

    return 0;
}