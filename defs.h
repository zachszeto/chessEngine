#ifndef DEFS_H
#define DEFS_H

typedef unsigned long long U64;

#define NAME "chessEngine 1.0"
#define BRD_SQ_NUM 120 //Board Array
#define MAXGAMEMOVES 2048 //How many moves we expect both players combined to make

enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK}; //Pieces (ie. wP = white Pawn, bN = black Knight, etc)
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE}; //File Def
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE}; //Rank Def
enum{WHITE, BLACK, BOTH}; //Colors

//Square Labels
enum{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};

enum{FALSE, TRUE};

enum{WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8}; //Castling Permissions

//Undo Move Struct
typedef struct 
{
    int move;
    int casetlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey;

} S_UNDO;

//Board Setup Struct
typedef struct
{
    int pieces[BRD_SQ_NUM];         // Board Array
    U64 pawns[3];                   // Array of Pawns
    int KingSq[2];                  // Kings' squares
    int side;                       // Side to move
    int enPas;                      // Enpassant Square
    int fiftyMove;                  // Fifty move counter (Fifty moves without capture or pawn move is a draw by repetition)
    int ply;                        // Current Move
    int hisPly;                     // Past Moves
    U64 posKey;                     // Unique key for each board position
    int pceNum[13];                 // Number of pieces on the board indexed by piece type
    int bigPce[3];                  // Number of 'big pieces' on the board by color (not pawns)
    int mjrPce[3];                  // Number of 'major pieces' on the board by color (Rooks and Queens)
    int minPce[3];                  // Number of 'minor pieces' on the board by color (Bishops and Knights)
    int castlePerm;                 //Castling Permissions
    S_UNDO history[MAXGAMEMOVES];   //Everytime a move is made we store it in this array
} S_BOARD;



#endif