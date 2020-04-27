#include <stdio.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R |
 */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    printf("     ****** The Board ******\n");
    printf("    0   1   2   3   4   5   6   7 \n"
           "");
    for(int i = 0; i < BOARD_SIZE; i ++){
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|   ");
                else{
                    if (board[i][j].stack->piece_color == GREEN) {
                        printf("| G ");
                    }
                    else{
                        printf("| R ");
                    }
                }
            }
            else
                printf("| - ");
        }
        printf("|\n");
    }
}

int userInputInt(char *string){
    /*
     * Display request to user
     * Read in from user
     * Return value read in
     */
    int result;

    printf("%s", string);
    scanf("%d", &result);

    return result;
}

/*
 * Function prints:
 * Number of pieces on and
 * order of pieces on given square
 */
void squareStatusPrinter(square *statusSquare){
    square *current = statusSquare; /* Cannot access data in passed pointer without changing so use another pointer */
    /*
     * Number of pieces on square
     */
    printf("\nThe number of pieces on this square is: %d\n", current->num_pieces);

    /*
     * Display pieces in their order
     */
    puts("The stack contains the following pieces:");
    while(current->stack->next != NULL){ /* Navigate through stack */
        if(current->stack->piece_color == RED){
            printf("R --> ");
        }
        else{
            printf("G --> ");
        }
        current->stack = current->stack->next;
    }
    /*
     * Print final piece
     */
    if(current->stack == RED) {
        printf("R\n\n");
    }
    else{
        printf("G\n\n");
    }
}

/*
 * function to print
 * Given player name
 * given player colour
 * given player's own pieces kept
 * given player's pieces captured
 */

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