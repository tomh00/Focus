//
// Created by tom on 18/04/2020.
//
#include "game_init.h"
#include "moves.h"
#include "turns.h"
#include "input_output.h"
#include <stdio.h>

void turnManager(bool lastTurn[], player players[], square board[BOARD_SIZE][BOARD_SIZE]){
    int line, column; /* Variables to hold index */
    bool validSquare = false; /* Loop break variable */
    player *currentPlayer = &players[currentTurn(lastTurn)]; /* Call currentTurn for currentPlayer assignment */

    /*
     * Loop to take user input of indices and check that they are valid in the current state of the game
     */
    while(!validSquare) {
        /*
         * Ask player for indices and read them into memory using userInputInt function
         */
        printf("%s:\n", currentPlayer->playerName);
        line = userInputInt("Enter the index of the line of the piece you would like to move: ");
        column = userInputInt("Enter the index of the column of the piece you would like to move: ");

        /*
         * If square chosen is
         * INVALID
         * Empty
         * or containing a stack that is not the current player's colour on top
         * Print error message reset turn managing array and re enter loop
         */
        if (checkValidity(&board[line][column], line, column) == INVALID ||
            testEmpty(&board[line][column]) || !testColour(&board[line][column], currentPlayer)) {
            puts("You cannot move this piece!"
                 "\nPlease ensure you pick a square with a piece on it and a stack with your colour at the top!");
            resetLastTurn(lastTurn); /* reset boolean array to repeat user turn */
        }
            else{
            validSquare = true; /* break condition satisfied */
        }
    }

    movementManager(line, column, board, currentPlayer);
}

int currentTurn(bool lastTurn[]){
    /*
     * If player did not go last, adjust array for next turn
     * return corresponding number
     */
    if(!lastTurn[0]){
        lastTurn[0] = true;
        lastTurn[1] = false;
        return 0;
    }
    else{
        lastTurn[0] = false;
        lastTurn[1] = true;
        return 1;
    }
}

bool testEmpty(square *testSquare){
    bool empty = false;

    /*
     * if the stack points to NULL the square is empty
     */
    if(testSquare->stack == NULL){
        empty = true;
    }

    return empty;
}

bool testColour(square *testPiece, player *currentPlayer){
    /*
     * if the piece colour and player colour are the same return true, else return false
     */
    if(testPiece->stack->piece_color == currentPlayer->player_color){
        return true;
    }
    return false;
}

void resetLastTurn(bool *lastTurn){
    /*
     * Test orientation of lastTurn array
     * Swap the setup
     */
    if(lastTurn[0] == true){
        lastTurn[0] = false;
        lastTurn[1] = true;
    }
    else{
        lastTurn[0] = true;
        lastTurn[1] = false;
    }
}