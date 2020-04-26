//
// Created by tom on 06/04/2020.
//
#include "game_init.h"
#include "moves.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void movementManager(int line, int column, square board[BOARD_SIZE][BOARD_SIZE], player *currentPlayer){
    int input;
    int movement = board[line][column].num_pieces; /* Number of squares that the piece selected can be moved */
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
                if (checkValidity(&board[line - movement][column], line-movement, column) == INVALID) {
                    break;
                }
                else{
                    board[line - movement][column].stack = stack(board[line][column].stack, board[line - movement][column].stack); /* Stack stacks together */
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
                if(checkValidity(&board[line + movement][column], line+movement, column) == INVALID){
                    break;
                }
                else{
                    board[line + movement][column].stack = stack(board[line][column].stack, board[line + movement][column].stack); /* Stack stacks together */
                    board[line][column].stack = NULL; /* This square no longer points to moved piece */
                    pieceNumManager(&board[line + movement][column], &board[line][column], currentPlayer); /* Adjust number of pieces on each square accordingly */
                }
                validMove = true; /* End of loop condition satisfied */
                break;

            case 3:
                if(checkValidity(&board[line][column - movement], column-movement, line) == INVALID){
                    break;
                }
                else{
                    board[line][column - movement].stack = stack(board[line][column].stack, board[line][column - movement].stack); /* Stack stacks together */
                    board[line][column].stack = NULL; /* This square no longer points to moved piece */
                    pieceNumManager(&board[line][column - movement], &board[line][column], currentPlayer); /* Adjust number of pieces on each square accordingly */
                }
                validMove = true; /* End of loop condition satisfied */
                break;

            case 4:
                if(checkValidity(&board[line][column + movement], column+movement, line) == INVALID){
                    break;
                }
                else{
                    board[line][column + movement].stack = stack(board[line][column].stack, board[line][column + movement].stack); /* Stack stacks together */
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

square_type checkValidity(square *testSquare, int testIndex1, int testIndex2){
    /*
     * Check if square is valid or invalid or if it is contained on the board
     * return Valid or Invalid
     */
    if(testSquare->type == INVALID || testIndex1 < 0 || testIndex1 > 7 || testIndex2 < 0 || testIndex2 > 7){
        puts("There are not enough squares to move this piece in this direction!\n"
             "Please try again:\n");
        return INVALID;
    }
    else{
        return VALID;
    }
}

piece * stack(piece *topPiece1, piece *topPiece2){
    piece *current = topPiece1; /* Piece pointer to navigate through the stack */

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