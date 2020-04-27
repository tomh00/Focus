#include <stdio.h>

#include "input_output.h"
#include <stdbool.h>
#include "moves.h"
#include "winning_condtion.h"
#include "turns.h"
#include <stdlib.h>

int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    /* Initialise player details and details of each square of the board
     * Display Board
     */
    initialize_players(players);

    initialize_board(board);

    print_board(board);

    bool lastTurn[] = {false, false}; /* Boolean array to maintain turns of the game */

    bool endGame = false;
    player *currentPlayer;
    currentPlayer = turnManager(lastTurn, players, board); /* Takes care of player movement */
    print_board(board);

    while(!endGame) {
        /*
         *
         */
        if(topPieceFinder(board, currentPlayer->player_color ) || reservedPieceChecker(currentPlayer)){
            currentPlayer = turnManager(lastTurn, players, board); /* Takes care of player movement */
            print_board(board);
        }
        else{
            endGame = true;
        }
    }

    return 0;
}
