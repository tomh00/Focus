//
// Created by tom on 06/04/2020.
//
#include "game_init.h"
#include "player_moves.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void movementManager(int line, int column, square board[BOARD_SIZE][BOARD_SIZE]);

bool * turnManager(bool lastTurn[], player players[], square board[BOARD_SIZE][BOARD_SIZE]) {
    int line, column;

    int playerNum;
    for (bool validColor = false; validColor != true;) {
        if (!lastTurn[0]) { /* Use test array to determine which player should move next*/
            printf("%s:\nEnter the index of the square of the piece you would like to move\nEnter the line first, then column:\n",
                   players[0].playerName); /* Request piece location of piece to be moved */
            scanf("%d%d", &line, &column);
            /* Adjust turn management variables */
            lastTurn[0] = true;
            lastTurn[1] = false;
            playerNum = 0;
        }
        /*
         * Repeat same process for other player in the case of the other player's turn
         */
        else {
            printf("%s:\nEnter the index of the square of the piece you would like to move\nEnter the line first, then column:\n",
                   players[1].playerName);
            scanf("%d%d", &line, &column);
            lastTurn[1] = true;
            lastTurn[0] = false;
            playerNum = 1;
        }

        /*
         * Check validity of square selection
         * If invalid, reset turn manager array
         */
        if ((line) < 0 || line > 7 || column < 0 || column > 7 || board[line][column].type == INVALID || board[line][column].stack == NULL) {
            puts("This is not a valid square to select! Please try again");
            if (lastTurn[0]) {
                lastTurn[0] = false;
                lastTurn[1] = true;
            } else {
                lastTurn[0] = true;
                lastTurn[1] = false;
            }
        }
        /*
         * If valid square is selected check player colour and piece colour match
         * if they do not match reset turn manager array
         */
        else if (board[line][column].stack->piece_color != players[playerNum].player_color) {
            puts("You have chosen a piece that is not yours to move! Please try again:");
            if (lastTurn[0]) {
                lastTurn[0] = false;
                lastTurn[1] = true;
            }
            else {
                lastTurn[0] = true;
                lastTurn[1] = false;
            }
        }
        else{
            validColor = true; /* Valid conditions met: break from loop */
        }
    }

    movementManager(line, column, board);

    return lastTurn;
}

void movementManager(int line, int column, square board[BOARD_SIZE][BOARD_SIZE]){
    int input;
    printf("You can move this piece %d squares" /* Pieces can be moved the size of the stack */
           "\nPlease indicate:"
           "\n 1 for UP"
           "\n 2 for DOWN"
           "\n 3 for LEFT"
           "\n 4 for RIGHT", board[line][column].num_pieces);
    scanf("%d", &input); /* Take in direction of movement from user */

    int movement = board[line][column].num_pieces; /* Movement allowed variable */
    piece *current = malloc(sizeof(piece));
    current = board[line][column].stack;
    bool validMove = false; /* Boolean to determine when to break from loop */
    while(!validMove) {
        switch (input) {
            case 1:
                /* Determine whether the piece can be moved this far in this direction
                 * If not break from switch
                 */
                if ((line - movement) < 0 || board[line - movement][column].type == INVALID) {
                    puts("There are not enough squares in this direction for this move!"
                         "\n Please try again.");
                    break;
                }
                else{
                    /*
                     * Navigate to bottom of stack
                     */
                    while(current->next != NULL){
                        current = current->next;
                    }
                    current->next = board[line - movement][column].stack; /* Link to top piece of other stack */
                    board[line - movement][column].stack = board[line][column].stack; /* Set new top piece to top piece of moved stack, which is now linked appropriately */
                    board[line][column].stack = NULL; /* This square no longer points to moved piece */
                    board[line - movement][column].num_pieces += board[line][column].num_pieces; /* Adjust number of pieces in new stack by addition of both stack numers */
                    board[line][column].num_pieces = 0; /* Adjust number of pieces on square which was moved from to 0 */
                    validMove = true; /* End of loop condition satisfied */
                }
                break;

            /*
             * Repeat similar process for other 3 directions possible
             * change piece to be moved to with manipulation of +/- operators on line and column of the piece being moved
             */
            case 2:
                if((line + movement) > 7 || board[line + movement][column].type == INVALID){
                    puts("There are not enough squares in this direction for this move!"
                         "\n Please try again");
                    break;
                }
                else{
                    while(current->next != NULL){
                        current = current->next;
                    }
                    current->next = board[line + movement][column].stack;
                    board[line+movement][column].stack = board[line][column].stack;
                    board[line][column].stack = NULL;
                    board[line + movement][column].num_pieces += board[line][column].num_pieces;
                    board[line][column].num_pieces = 0;
                    validMove = true;
                }
                break;

            case 3:
                if((column - movement) < 0 || board[line][column - movement].type == INVALID){
                    puts("There are not enough squares in this direction for this move!"
                         "\n Please try again");
                    break;
                }
                else{
                    while(current->next != NULL){
                        current = current->next;
                    }
                    current->next = board[line][column - movement].stack;
                    board[line][column - movement].stack = board[line][column].stack;
                    board[line][column].stack = NULL;
                    board[line][column - movement].num_pieces += board[line][column].num_pieces;
                    board[line][column].num_pieces = 0;
                    validMove = true;
                }
                break;

            case 4:
                if((column + movement) > 7 || board[line][column + movement].type == INVALID){
                    puts("There are not enough squares in this direction for this move!"
                         "\n Please try again");
                    break;
                }
                else{
                    while(current->next != NULL){
                        current = current->next;
                    }
                    current->next = board[line][column + movement].stack;
                    board[line][column + movement].stack = board[line][column].stack;
                    board[line][column].stack = NULL;
                    board[line][column + movement].num_pieces += board[line][column].num_pieces;
                    board[line][column].num_pieces = 0;
                    validMove = true;
                }
                break;
        }
    }
}

