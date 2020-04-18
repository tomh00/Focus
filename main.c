#include <stdio.h>

#include "input_output.h"
#include <stdbool.h>
#include "moves.h"
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

    for(int i = 0; i < 20; i ++) {
        turnManager(lastTurn, players, board); /* Takes care of player movement */
        print_board(board);
    }

    return 0;
}
