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
        if (!lastTurn[0]) {
            printf("%s:\nEnter the index of the square of the piece you would like to move\nEnter the line first, then column:\n",
                   players[0].playerName);
            scanf("%d%d", &line, &column);
            lastTurn[0] = true;
            lastTurn[1] = false;
            playerNum = 0;
        }
        else {
            printf("%s:\nEnter the index of the square of the piece you would like to move\nEnter the line first, then column:\n",
                   players[1].playerName);
            scanf("%d%d", &line, &column);
            lastTurn[1] = true;
            lastTurn[0] = false;
            playerNum = 1;
        }
        if (board[line][column].stack->piece_color != players[playerNum].player_color) {
            puts("You have chosen a piece that is not yours to move! Please try again:");
            break;
        }
        if((line) < 0 || board[line][column].type == INVALID){
            puts("This is not a valid square to select! Please try again");
            break;
        }
        else{
            validColor = true;
        }
    }

    movementManager(line, column, board);

    return lastTurn;
}

void movementManager(int line, int column, square board[BOARD_SIZE][BOARD_SIZE]){
    int input;
    printf("You can move this piece %d squares"
           "\nPlease indicate:"
           "\n 1 for UP"
           "\n 2 for DOWN"
           "\n 3 for LEFT"
           "\n 4 for RIGHT", board[line][column].num_pieces);
    scanf("%d", &input);

    int movement = board[line][column].num_pieces;
    piece *current = malloc(sizeof(piece));
    current = board[line][column].stack;
    bool validMove = false;
    while(!validMove) {
        switch (input) {
            case 1:
                if ((line - movement) < 0 || board[line - movement][column].type == INVALID) {
                    puts("There are not enough squares in this direction for this move!"
                         "\n Please try again.");
                    break;
                }
                else{
                    while(current->next != NULL){
                        current = current->next;
                    }
                    current->next = board[line - movement][column].stack;
                    board[line - movement][column].stack = board[line][column].stack;
                    board[line][column].stack = NULL;
                    board[line - movement][column].num_pieces += board[line][column].num_pieces;
                    board[line][column].num_pieces = 0;
                    validMove = true;
                }
                break;
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


