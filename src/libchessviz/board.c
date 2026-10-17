#include "board.h"
#include "board_move.h"
#include <stdio.h>
#include <string.h>

void board_init(Board* board)
{
    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            board->squares[row][col] = EMPTY;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        board->squares[1][i] = WHITE_PAWN;
        board->squares[6][i] = BLACK_PAWN;
    }

    board->squares[0][0] = WHITE_ROOK;   board->squares[0][7] = WHITE_ROOK;
    board->squares[7][0] = BLACK_ROOK;   board->squares[7][7] = BLACK_ROOK;
    board->squares[0][1] = WHITE_KNIGHT; board->squares[0][6] = WHITE_KNIGHT;
    board->squares[7][1] = BLACK_KNIGHT; board->squares[7][6] = BLACK_KNIGHT;
    board->squares[0][2] = WHITE_BISHOP; board->squares[0][5] = WHITE_BISHOP;
    board->squares[7][2] = BLACK_BISHOP; board->squares[7][5] = BLACK_BISHOP;
    board->squares[0][3] = WHITE_QUEEN;  board->squares[0][4] = WHITE_KING;
    board->squares[7][3] = BLACK_QUEEN;  board->squares[7][4] = BLACK_KING;
    
    board->turn = 0;
}

bool is_white(Piece p)
{
    return p >= WHITE_PAWN && p <= WHITE_KING;
}

static char piece_to_char(Piece p)
{
    switch (p) {
        case WHITE_PAWN:   return 'P';
        case WHITE_ROOK:   return 'R';
        case WHITE_KNIGHT: return 'N';
        case WHITE_BISHOP: return 'B';
        case WHITE_QUEEN:  return 'Q';
        case WHITE_KING:   return 'K';
        case BLACK_PAWN:   return 'p';
        case BLACK_ROOK:   return 'r';
        case BLACK_KNIGHT: return 'n';
        case BLACK_BISHOP: return 'b';
        case BLACK_QUEEN:  return 'q';
        case BLACK_KING:   return 'k';
        default:           return '.';
    }
}

void board_print(const Board* board, FILE* out)
{
    fprintf(out, "\n  a b c d e f g h\n");
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        fprintf(out, "%d ", row + 1);
        for (int col = 0; col < BOARD_SIZE; col++)
            fprintf(out, "%c ", piece_to_char(board->squares[row][col]));
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

bool is_valid_move(Board* board, int from_row, int from_col, int to_row, int to_col)
{
    Piece piece = board->squares[from_row][from_col];
    if (piece == EMPTY) return false;

    Piece target = board->squares[to_row][to_col];
    if (target != EMPTY && is_white(piece) == is_white(target))
        return false;

    bool capture = (target != EMPTY);
    bool white = is_white(piece);

    switch (piece) {
        case WHITE_PAWN: case BLACK_PAWN:
            return valid_pawn_move(from_row, from_col, to_row, to_col, capture, white);
        case WHITE_ROOK: case BLACK_ROOK:
            return valid_rook_move(board, from_row, from_col, to_row, to_col);
        case WHITE_KNIGHT: case BLACK_KNIGHT:
            return valid_knight_move(from_row, from_col, to_row, to_col);
        case WHITE_BISHOP: case BLACK_BISHOP:
            return valid_bishop_move(board, from_row, from_col, to_row, to_col);
        case WHITE_QUEEN: case BLACK_QUEEN:
            return valid_queen_move(board, from_row, from_col, to_row, to_col);
        case WHITE_KING: case BLACK_KING:
            return valid_king_move(from_row, from_col, to_row, to_col);
        default:
            return false;
    }
}

bool board_apply_move(Board* board, const char* move)
{
    if (strlen(move) < 4) return false;

    int from_col = move[0] - 'a';
    int from_row = move[1] - '1';
    int to_col = move[3] - 'a';
    int to_row = move[4] - '1';

    if (from_row < 0 || from_row >= BOARD_SIZE || from_col < 0 || from_col >= BOARD_SIZE ||
        to_row < 0 || to_row >= BOARD_SIZE || to_col < 0 || to_col >= BOARD_SIZE)
        return false;

    Piece piece = board->squares[from_row][from_col];

    if ((board->turn == 0 && !is_white(piece)) || (board->turn == 1 && is_white(piece)))
        return false;

    if (!is_valid_move(board, from_row, from_col, to_row, to_col))
        return false;

    board->squares[to_row][to_col] = piece;
    board->squares[from_row][from_col] = EMPTY;

    board->turn = !board->turn;
    return true;
}

const char* board_get_turn(Board* board)
{
    return board->turn == 0 ? "White" : "Black";
}