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
         *  Keep iterating through turns of the game until there are no more of a players colour top pieces and that player has no more reserved pieces
         */
        if(topPieceFinder(board, currentPlayer->player_color ) || reservedPieceChecker(currentPlayer)){
            currentPlayer = turnManager(lastTurn, players, board); /* Takes care of player movement */
            print_board(board);
        }
        else{
            endGame = true;
        }
    }

    /*
     * Print information about winning player
     */
    if(nextTurn(lastTurn) == 0) {
        printf("%s Wins! \nPlayer details:\n", players[0].playerName);
        playerStatusPrinter(&players[0]);
    }
    else{
        printf("%s Wins! \nPlayer details:\n", players[1].playerName);
        playerStatusPrinter(&players[1]);
    }

    return 0;
}
