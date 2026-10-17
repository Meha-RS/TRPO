#pragma once

#include <stdbool.h>
#include <stdio.h>

#define BOARD_SIZE 8

typedef enum {
    EMPTY,
    WHITE_PAWN,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_QUEEN,
    WHITE_KING,
    BLACK_PAWN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_QUEEN,
    BLACK_KING
} Piece;

typedef struct {
    Piece squares[BOARD_SIZE][BOARD_SIZE];
    int turn;
} Board;

void board_init(Board* board);
void board_print(const Board* board, FILE* out);
bool board_apply_move(Board* board, const char* move);
bool is_valid_move(Board* board, int from_row, int from_col, int to_row, int to_col);
bool is_white(Piece p);
const char* board_get_turn(Board* board);