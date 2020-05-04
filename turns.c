//
// Created by tom on 18/04/2020.
//
#include "game_init.h"
#include "moves.h"
#include "turns.h"
#include "input_output.h"
#include "winning_condtion.h"
#include <stdio.h>
#include <stdlib.h>

player * turnManager(bool lastTurn[], player players[], square board[BOARD_SIZE][BOARD_SIZE]){
    int line, column; /* Variables to hold index */
    bool validSquare = false; /* Loop break variable */
    player *currentPlayer = &players[currentTurn(lastTurn)]; /* Call currentTurn for currentPlayer assignment */
    player *nextPlayer = &players[nextTurn(lastTurn)];

    playerStatusPrinter(currentPlayer); /* Show current player their current status */
    /*
     * Offer to show user the status of any of the squares on the board
     * use squareStatusPrinter function to show these squares
     * user can input 0 or 1 for their choice but loop continues until 1 (the continue choice is inputted)
     */

    for (bool moveOn = false; !moveOn;) {
        int input = userInputInt("Enter 0 if you would like to see the status of any square or 1 if you would like to proceed with your turn: ");
        if (input == 0) {
            /*
             * Establish square user would like to view
             */
            line = userInputInt("Enter the index of the line of the piece you would like to see the status of: ");
            column = userInputInt("Enter the index of the column of the piece you would like to see the status of: ");
            squareStatusPrinter(&board[line][column], board[line][column].stack); /* Print status of this square */
        }
        else if(input == 1){
            moveOn = true; /* If user chooses to continue boolean break condition becomes true */
        }
        else{
            puts("Please enter either 1 or 0!"); /* error message when user does not enter 0 or 1 */
        }
    }

    /*
     * If player has no more top pieces of their colour they must place a piece
     */
    if(!topPieceFinder(board, currentPlayer->player_color)){
        puts("You have no pieces to move! You must place a reserved piece down!");
        placeKeptPieces(currentPlayer, board);
        return nextPlayer;
    }

    /*
     * Offer the user to place a kept piece of theirs if they have any
     */
    if(currentPlayer->piecesKept > 0){
        if(userInputInt("Enter 0 to move a stack on the board or 1 to place a kept piece on the board: ") == 1){
            placeKeptPieces(currentPlayer, board);
            return nextPlayer;
        }
    }

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
        }
        else{
            validSquare = true; /* break condition satisfied */
        }
    }

    movementManager(line, column, board, currentPlayer);

    return nextPlayer;
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

int nextTurn(bool lastTurn[]){
    /*
     * If player did not go last, adjust array for next turn
     * return corresponding number
     */
    if(!lastTurn[0]){
        return 0;
    }

        return 1;
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

void placeKeptPieces(player *currentPlayer, square board[BOARD_SIZE][BOARD_SIZE]){
    int line, column;

    puts("\nWhere would you like to place your piece:");
    line = userInputInt("Enter the line number of the square: ");
    column = userInputInt("Enter the column number of the square: ");

    piece *keptPiece = malloc(sizeof(piece));
    keptPiece->piece_color = currentPlayer->player_color;
    stack(keptPiece, board[line][column].stack);
    board[line][column].stack = keptPiece;
    currentPlayer->piecesKept -= 1;

    if(board[line][column].num_pieces > 5){
        pieceNumManager(&board[line][column], NULL, currentPlayer);
    }
}
