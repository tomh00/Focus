#ifndef FOCUS_GAME_INIT_H
#define FOCUS_GAME_INIT_H



#define BOARD_SIZE 8
#define PLAYERS_NUM 2
#define MAX_NAME 20

//colors that a piece can have
typedef enum color {
    RED,
    GREEN
}color;

// Square types
//INVALID: squares that are on the sides and where no piece can be placed
//VALID: squares where it is possible to place a piece or a stack
typedef enum square_type {
    VALID,
    INVALID
}square_type;

//Player
/*
 * Referenced by:
 * Player color
 * Player name
 * Number of captured adversary pieces
 * Number of own pieces kept
 */
typedef struct player{
    color player_color;
    char playerName[MAX_NAME];
    int capturedPieces;
    int piecesKept;
}player;

// A piece
typedef struct piece {
    //the color associated with a piece
    color piece_color;

    // This is a pointer to the next pieces
    // to create a stack. For lab 1 you do not have to think too much about it.
    struct piece * next;

}piece;

// A Square of the board
typedef struct square {
    // type of the square (VALID/INVALID)
    square_type type;

    //the piece or the top piece on the stack
    piece * stack;

    //number of pieces on the square
    int num_pieces;

}square;

//Function to create the players
void initialize_players(player players[PLAYERS_NUM]);

//Function to create the board
void initialize_board(square board[BOARD_SIZE][BOARD_SIZE]);





#endif //FOCUS_GAME_INIT_H