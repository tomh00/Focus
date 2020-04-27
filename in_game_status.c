//
// Created by tom on 4/26/20.
//

#include "in_game_status.h"
#include "stdio.h"

void squareStatusPrinter(square *statusSquare){
    printf("\nThe number of pieces on this square is: %d\n", statusSquare->num_pieces);

    puts("The stack contains the following pieces:");
    while(statusSquare->stack->next != NULL){
        if(statusSquare->stack->piece_color == RED){
            printf("R --> ");
        }
        else{
            printf("G --> ");
        }
        statusSquare->stack = statusSquare->stack->next;
    }
    if(statusSquare->stack == RED) {
        printf("R\n\n");
    }
    else{
        printf("G\n\n");
    }
}

void playerStatusPrinter(player *currentPlayer){
    printf("Player Name: %s\n", currentPlayer->playerName);
    if(currentPlayer->player_color == RED) {
        printf("Player Colour: RED\n");
    }
    else {
        printf("Player Colour: GREEN\n");
    }
    printf("Pieces Kept: %d\n", currentPlayer->piecesKept);
    printf("Piece Captured: %d\n", currentPlayer->capturedPieces);
    printf("\n");
}