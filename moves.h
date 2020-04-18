//
// Created by tom on 06/04/2020.
//

#ifndef FOCUS_PLAYER_MOVES_H
#define FOCUS_PLAYER_MOVES_H

#endif //FOCUS_PLAYER_MOVES_H

#include <stdbool.h>

void turnManager(bool lastTurn[], player players[], square board[BOARD_SIZE][BOARD_SIZE]);

void movementManager(int line, int column, square board[BOARD_SIZE][BOARD_SIZE], player *currentPlayer);

void removePieces(piece *last, player *currentPlayer);

void excessPieceControl(piece *removedPiece, player *currentPlayer);

void stackPiece(piece *, piece *);

square_type checkValidity(square *testSquare, int testIndex);

piece * stack(piece *top1, piece *top2);

void pieceNumManager(square *square1, square *square2, player *currentPlayer);