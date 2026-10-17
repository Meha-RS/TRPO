#include <libchessviz/board.h>
#include <string.h>

#define MAX_LINE 256

int main()
{
    Board board;
    board_init(&board);
    printf("Initial position:\n");
    board_print(&board, stdout);

    char line[MAX_LINE];
    int move_num = 1;

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0 || line[0] == '#')
            continue;

        printf("\n\n\n%d. %s (%s turn)\n", move_num, line, board_get_turn(&board));

        if (!board_apply_move(&board, line)) {
            fprintf(stderr, "Error: invalid move '%s'\n", line);
            continue;
        }

        board_print(&board, stdout);
        move_num++;
    }

    return 0;
}