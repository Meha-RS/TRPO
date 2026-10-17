#include "board_move.h"
#include <stdlib.h>

bool valid_pawn_move(
        int from_row,
        int from_col,
        int to_row,
        int to_col,
        bool capture,
        bool white)
{
    int direction = white ? 1 : -1;
    int start_row = white ? 1 : 6;

    if (!capture && to_col == from_col && to_row == from_row + direction)
        return true;

    if (!capture && from_row == start_row && to_col == from_col
        && to_row == from_row + 2 * direction)
        return true;

    if (capture && abs(to_col - from_col) == 1
        && to_row == from_row + direction)
        return true;

    return false;
}

bool valid_knight_move(
        int from_row,
        int from_col,
        int to_row,
        int to_col)
{
    int dr = abs(to_row - from_row);
    int dc = abs(to_col - from_col);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool valid_rook_move(
        const Board* board,
        int from_row,
        int from_col,
        int to_row,
        int to_col)
{
    if (from_row != to_row && from_col != to_col)
        return false;
    return is_clear_path(board, from_row, from_col, to_row, to_col);
}

bool valid_bishop_move(
        const Board* board,
        int from_row,
        int from_col,
        int to_row,
        int to_col)
{
    if (abs(to_row - from_row) != abs(to_col - from_col))
        return false;
    return is_clear_path(board, from_row, from_col, to_row, to_col);
}

bool valid_queen_move(
        const Board* board,
        int from_row,
        int from_col,
        int to_row,
        int to_col)
{
    if (from_row == to_row || from_col == to_col)
        return is_clear_path(board, from_row, from_col, to_row, to_col);
    if (abs(to_row - from_row) == abs(to_col - from_col))
        return is_clear_path(board, from_row, from_col, to_row, to_col);
    return false;
}

bool valid_king_move(
        int from_row,
        int from_col,
        int to_row,
        int to_col)
{
    int dr = abs(to_row - from_row);
    int dc = abs(to_col - from_col);
    return (dr <= 1 && dc <= 1 && !(dr == 0 && dc == 0));
}

bool is_clear_path(
        const Board* board,
        int from_row,
        int from_col,
        int to_row, 
        int to_col)
{
    int dr = (to_row - from_row == 0) ? 0 : (to_row - from_row) / abs(to_row - from_row);
    int dc = (to_col - from_col == 0) ? 0 : (to_col - from_col) / abs(to_col - from_col);

    int row = from_row + dr;
    int col = from_col + dc;

    while (row != to_row || col != to_col) {
        if (board->squares[row][col] != EMPTY)
            return false;
        row += dr;
        col += dc;
    }
    return true;
}