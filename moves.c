//
// Created by tom on 06/04/2020.
//
#include "game_init.h"
#include "moves.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void turnManager(bool lastTurn[], player players[], square board[BOARD_SIZE][BOARD_SIZE]) {
    int line, column;
    player *currentPlayer;

    for (bool validColor = false; validColor != true;) {
        if (!lastTurn[0]) { /* Use test array to determine which player should move next*/
            printf("%s:\nEnter the index of the square of the piece you would like to move\nEnter the line first, then column:\n",
                   players[0].playerName); /* Request piece location of piece to be moved */
            scanf("%d%d", &line, &column);
            /* Adjust turn management variables */
            lastTurn[0] = true;
            lastTurn[1] = false;
            currentPlayer = &players[0];
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
            currentPlayer = &players[1];
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
        else if (board[line][column].stack->piece_color != currentPlayer->player_color) {
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

    movementManager(line, column, board, currentPlayer);
}

void movementManager(int line, int column, square board[BOARD_SIZE][BOARD_SIZE], player *currentPlayer){
    int input;
    int movement = board[line][column].num_pieces; /* Movement allowed variable */
    bool validMove = false; /* Boolean to determine when to break from loop */

    while(!validMove) {
        printf("You can move this piece %d squares" /* Pieces can be moved the size of the stack */
               "\nPlease indicate:"
               "\n 1 for UP"
               "\n 2 for DOWN"
               "\n 3 for LEFT"
               "\n 4 for RIGHT", board[line][column].num_pieces);
        scanf("%d", &input); /* Take in direction of movement from user */
        switch (input) {
            case 1:
                /* Determine whether the piece can be moved this far in this direction
                 * If not break from switch
                 */
                if (checkValidity(&board[line - movement][column], line-movement) == INVALID) {
                    break;
                }
                else{
                    board[line - movement][column].stack = stack(&board[line][column].stack, &board[line - movement][column].stack); /* Stack stacks together */
                    board[line][column].stack = NULL; /* This square no longer points to moved piece */
                    pieceNumManager(&board[line - movement][column], &board[line][column], currentPlayer); /* Adjust number of pieces on each square accordingly */
                    }
                validMove = true; /* End of loop condition satisfied */
                break;

            /*
             * Repeat similar process for other 3 directions possible
             * change piece to be moved to with manipulation of +/- operators on line and column of the piece being moved
             */
            case 2:
                if(checkValidity(&board[line + movement][column], line+movement) == INVALID){
                    break;
                }
                else{
                    board[line + movement][column].stack = stack(&board[line][column].stack, &board[line + movement][column].stack); /* Stack stacks together */
                    board[line][column].stack = NULL; /* This square no longer points to moved piece */
                    pieceNumManager(&board[line + movement][column], &board[line][column], currentPlayer); /* Adjust number of pieces on each square accordingly */
                }
                validMove = true; /* End of loop condition satisfied */
                break;

            case 3:
                if(checkValidity(&board[line][column - movement], column-movement) == INVALID){
                    break;
                }
                else{
                    board[line][column - movement].stack = stack(&board[line][column].stack, &board[line][column - movement].stack); /* Stack stacks together */
                    board[line][column].stack = NULL; /* This square no longer points to moved piece */
                    pieceNumManager(&board[line][column - movement], &board[line][column], currentPlayer); /* Adjust number of pieces on each square accordingly */
                }
                validMove = true; /* End of loop condition satisfied */
                break;

            case 4:
                if(checkValidity(&board[line][column + movement], column+movement) == INVALID){
                    break;
                }
                else{
                    board[line][column + movement].stack = stack(&board[line][column].stack, &board[line][column + movement].stack); /* Stack stacks together */
                    board[line][column].stack = NULL; /* This square no longer points to moved piece */
                    pieceNumManager(&board[line][column + movement], &board[line][column], currentPlayer); /* Adjust number of pieces on each square accordingly */
                }
                validMove = true; /* End of loop condition satisfied */
                break;
        }
    }
}

/*
 * Function to remove excess pieces from bottom of a stack
 * only called when a stack reaches a size larger than 5
 */
void removePieces(piece *last, player *currentPlayer){
    int counter = 1;
    piece * current = NULL;
    piece * toRemove = NULL;

    /*
     * Traverse through the stack until we reach the 5th element
     */
    while(counter < 5){
        last = last->next;
        counter++;
    }

    /*
     * Last position must be held for later by the pointer last
     * Introduce pointer current to work further into stack
     */
    current = last;
    current = current->next;

    while(current != NULL){
        toRemove = current; /* Set element to be removed and move current on further */
        current = current->next;
        excessPieceControl(toRemove, currentPlayer); /* Allocate the kept piece correctly */
        free(toRemove); /* Deallocate memory pointed to by toRemove */
    }
    last->next = NULL; /* The last element of the stack must always point to NULL */
}

void excessPieceControl(piece * removedPiece, player *currentPlayer){
    /*
     * If piece removed is the same as player colour player must keep in keptPieces
     * Else the piece is discarded in capturedPieces
     */
    if (removedPiece->piece_color == currentPlayer->player_color){
        currentPlayer->piecesKept++;
    }
    else{
        currentPlayer->capturedPieces++;
    }
}

square_type checkValidity(square *testSquare, int testIndex){
    /*
     * Check if square is valid or invalid or if it is contained on the board
     * return Valid or Invalid
     */
    if(testSquare->type == INVALID || testIndex < 0 || testIndex > 7){
        puts("There are not enough squares to move this piece in this direction!\n"
             "Please try again:\n");
        return INVALID;
    }
    else{
        return VALID;
    }
}

piece * stack(piece *topPiece1, piece *topPiece2){
    piece *current = topPiece1; /* Piece pointer to navigate throught the stack */

    /*
     * Navigate to bottom of stack
     */
    while(current->next != NULL){
        current = current->next;
    }
    current->next = topPiece2; /* Link bottom piece of stack one to top piece of stack two */

    return topPiece1;
}

void pieceNumManager(square *square1, square *square2, player *currentPlayer){
    /*
     * The stacks on square 1 and square 2 have been stacked on one another at square 1
     * The number of pieces on square 1 becomes the addition of both stacks
     * The number of pieces on square 2 becomes 0
     */
    square1->num_pieces += square2->num_pieces;
    square2->num_pieces = 0;

    if(square1->num_pieces > 5){
        removePieces(square1->stack, currentPlayer);
        square1->num_pieces = 5;
    }
}