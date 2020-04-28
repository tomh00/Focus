//
// Created by tom on 4/27/20.
//

#include "winning_condtion.h"
#include "moves.h"
#include "turns.h"

bool topPieceFinder(square board[BOARD_SIZE][BOARD_SIZE], color currentPlayerColour){
    /*
     * Iterate through each square
     * Test colour of each top piece against colour passed into function
     * If the same colour is found return true
     * If same colour is not found return false
     */
    for(int line = 0; line < BOARD_SIZE; line++){
        for(int column = 0; column < BOARD_SIZE; column++){
            if(checkValidity(&board[line][column], line, column) == VALID && !testEmpty(&board[line][column])) {
                if (board[line][column].stack->piece_color == currentPlayerColour) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool reservedPieceChecker(player *currentPlayer){
    /*
     * Return false if current player does not have reserved pieces
     * else return true
     */
    if(currentPlayer->piecesKept == 0){
        return false;
    }
    return true;
}