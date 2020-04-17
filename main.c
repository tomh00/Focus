#include <stdio.h>

#include "input_output.h"
#include <stdbool.h>
#include "player_moves.h"
#include <stdlib.h>

int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    initialize_players(players);

    initialize_board(board);

    print_board(board);

    bool lastTurn[] = {false, false};

    turnManager(lastTurn, players, board);

    print_board(board);

    turnManager(lastTurn, players, board);

    print_board(board);

    return 0;
}
