#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"

void initialize_players(player players[PLAYERS_NUM]){
    /*
     * Set player colours: player one gets red, player two gets green.
     */
    players[0].player_color = RED;
    players[1].player_color = GREEN;

    /*
     * Ask for names of players 1 and 2 and read into the struct variables.
     */
    printf("Enter the name of player 1: ");
    scanf("%s", players[0].playerName);
    printf("Enter the name of player 2: ");
    scanf("%s", players[1].playerName);

    /*
     * Set the number of captured pieces to zero to begin with at the start of the game
     */
    players[0].capturedPieces = 0;
    players[1].capturedPieces = 0;

    /*
     * Set the number of own pieces saved to zero to begin with at the start of the game
     */
    players[0].piecesKept = 0;
    players[1].piecesKept = 0;
}

//Set Invalid Squares (where it is not possible to place stacks)
set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set squares  with a GREEN piece
set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->piece_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
}

//Set squares with a RED piece
set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->piece_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}

