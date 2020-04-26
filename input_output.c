#include <stdio.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R |
 */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    printf("****** The Board ******\n");
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