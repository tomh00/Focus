//
// Created by tom on 18/04/2020.
//

#include <stdbool.h>

#ifndef FOCUS_TURNS_H
#define FOCUS_TURNS_H

#endif //FOCUS_TURNS_H

void turnManager(bool lastTurn[], player players[], square board[BOARD_SIZE][BOARD_SIZE]);

int currentTurn(bool lastTurn[]);

bool testEmpty(square *testSquare);

bool testColour(square *testPiece, player *currentPlayer);

void resetLastTurn(bool *lastTurn);