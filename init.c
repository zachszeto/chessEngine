//init.c

#include "defs.h"

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

void InitBitMasks(){
    int index = 0;

    //Initializing Bit Mask
    for(index = 0; index < 64; index++){
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }

    //Setting Values for Bit Mask
    for(index = 0; index < 64; index++){
        SetMask[index] |= (1ULL << index);  //Index-th element is set to 1 all others are 0
        ClearMask[index] =  ~SetMask[index];//Index-th element is set to 0 all others are 1
    }
}

void InitSq120To64(){
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq  = A1;
    int sq64 = 0;

    //Iterating through each square in the array and setting value to 65   
    for(index = 0; index < BRD_SQ_NUM; ++index){
        Sq120ToSq64[index] = 65; //Failsafe should never actually be 65
    }

    //Iterating through each square in the array and setting value to 120
     for(index = 0; index < 64; ++index){
        Sq64ToSq120[index] = 120; //Failsafe should never actually be 120
    }

    //Going through all ranks and files to set Sq64ToSq120 and Sq120ToSq64 for each square
    for(rank = RANK_1; rank <= RANK_8; rank++){
        for(file = FILE_A; file <= FILE_H; ++file){
            sq = FR2SQ(file, rank);
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }


}

void AllInit(){
     InitSq120To64();
     InitBitMasks();
}