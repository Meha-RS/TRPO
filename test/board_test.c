#include <ctest.h>
#include <libchessviz/board.h>

CTEST(pawn, one_step_forward)
{
    Board b;
    board_init(&b);
    ASSERT_TRUE(is_valid_move(&b, 1, 4, 2, 4));
}

CTEST(pawn, double_step_from_start)
{
    Board b;
    board_init(&b);
    ASSERT_TRUE(is_valid_move(&b, 1, 4, 3, 4));
}

CTEST(pawn, cannot_move_backward)
{
    Board b;
    board_init(&b);
    ASSERT_FALSE(is_valid_move(&b, 1, 4, 0, 4));
}

CTEST(knight, from_b1_to_c3)
{
    Board b;
    board_init(&b);
    ASSERT_TRUE(is_valid_move(&b, 0, 1, 2, 2));
}

CTEST(knight, from_b1_to_a3)
{
    Board b;
    board_init(&b);
    ASSERT_TRUE(is_valid_move(&b, 0, 1, 2, 0));
}

CTEST(rook, vertical_move)
{
    Board b;
    board_init(&b);
    b.squares[1][0] = EMPTY;
    ASSERT_TRUE(is_valid_move(&b, 0, 0, 1, 0));
}

CTEST(rook, horizontal_move)
{
    Board b;
    board_init(&b);
    b.squares[0][1] = EMPTY;
    ASSERT_TRUE(is_valid_move(&b, 0, 0, 0, 1));
}

CTEST(bishop, diagonal_move)
{
    Board b;
    board_init(&b);
    b.squares[1][4] = EMPTY;
    b.squares[1][5] = EMPTY;
    ASSERT_TRUE(is_valid_move(&b, 0, 5, 3, 2));
}

CTEST(queen, vertical_move)
{
    Board b;
    board_init(&b);
    b.squares[1][3] = EMPTY;
    ASSERT_TRUE(is_valid_move(&b, 0, 3, 1, 3));
}

CTEST(queen, diagonal_move)
{
    Board b;
    board_init(&b);
    b.squares[1][3] = EMPTY;
    b.squares[1][4] = EMPTY;
    ASSERT_TRUE(is_valid_move(&b, 0, 3, 1, 4));
}

CTEST(king, one_step_forward)
{
    Board b;
    board_init(&b);
    b.squares[1][4] = EMPTY;
    ASSERT_TRUE(is_valid_move(&b, 0, 4, 1, 4));
}

CTEST(invalid, pawn_cannot_move_like_knight)
{
    Board b;
    board_init(&b);
    ASSERT_FALSE(is_valid_move(&b, 1, 4, 3, 5));
}