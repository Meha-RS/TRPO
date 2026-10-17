#pragma once

#include "board.h"

bool valid_pawn_move(
        int from_row,
        int from_col,
        int to_row,
        int to_col,
        bool capture,
        bool white);

bool valid_knight_move(
        int from_row,
        int from_col,
        int to_row,
        int to_col);

bool valid_rook_move(
        const Board* board,
        int from_row,
        int from_col,
        int to_row,
        int to_col);

bool valid_bishop_move(
        const Board* board,
        int from_row,
        int from_col,
        int to_row,
        int to_col);

bool valid_queen_move(
        const Board* board,
        int from_row,
        int from_col,
        int to_row,
        int to_col);

bool valid_king_move(
        int from_row,
        int from_col,
        int to_row,
        int to_col);

bool is_clear_path(
        const Board* board,
        int from_row,
        int from_col,
        int to_row, 
        int to_col);