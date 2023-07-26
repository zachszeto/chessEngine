#include "stdio.h"
#include "defs.h"

void PrintBitBoard(U64 bb){
    
    U64 shiftMe = 1ULL;

    int rank = 0;
    int file =0;
    int sq = 0;
    int sq64 = 0;

    //Prints Bit Map
    printf("\n");
    for(rank = RANK_8; rank >= RANK_1; --rank){
        for(file = FILE_A; file <= FILE_H; ++file){
            sq = FR2SQ(file, rank); //120 Based
            sq64 = SQ64(sq); //64 Based

            //Populating BitMap with "X" if piece is there else "-"
            if((shiftMe << sq64) & bb)
                printf("X");
            else
                printf("-");

        }
        printf("\n");
    }    
    printf("\n\n");
}