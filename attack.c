#include "defs.h"

const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir = {-9, -11, 11, 9};
const int KiDir = {-1, -10, 1, 10, -9, -11, 11, 9};

int SqAttacked(const sq, const int side, const S_BOARD *pos){
    int pce, index, t_sq, dir;

    //Pawns
    if(side == WHITE){
        if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP){
            return TRUE;
        } else {
            if(pos->pieces[sq+11] == wP || pos->pieces[sq+9] == bP){
            return TRUE;
        }
        }
    }
}