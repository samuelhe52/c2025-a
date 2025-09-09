#include <stdlib.h>
#include <ncurses.h>

#define WALL '#'
#define SPACE ' '
#define PLAYER 'P'
#define EXIT 'E'
#define MAZE_SIZE 20

struct pos {
    int x;
    int y;
};

int maze[MAZE_SIZE][MAZE_SIZE] = {};
struct pos person_pos;
struct pos exit_pos;

void initialize_maze(void) {
    FILE *fp = fopen(LAYOUT_FILE_PATH, "r");
    if (fp == NULL) {
        perror("Error opening layout file");
        exit(EXIT_FAILURE);
    }

    // Fill the maze with data from file
    for (int i = 0; i < MAZE_SIZE; i++) {
        char line[100] = {};
        fgets(line, 100, fp);
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (line[j] == PLAYER) {
                maze[i][j] = PLAYER;
                person_pos.x = i;
                person_pos.y = j;
                continue;
            }
            if (line[j] == EXIT ) {
                exit_pos.x = i;
                exit_pos.y = j;
            }
            maze[i][j] = (line[j] == '1') ? WALL : SPACE;
        }
    }

    fclose(fp);
}

void print_maze_debug(void) {
    for (int row = 0; row < MAZE_SIZE; row++) {
        if (row == 0) {
            printw("\t");
            for (int col = 0; col < MAZE_SIZE; col++) {
                printw("%02d ", col + 1);
            }
            printw("\n");
        }
        printw("%02d\t", row + 1);
        for (int col = 0; col < MAZE_SIZE; col++) {
            printw("%c", maze[row][col]);
            printw("%c", SPACE);
        }
        printw("\n");
    }
}

void print_maze(void) {
    for (int row = 0; row < MAZE_SIZE; row++) {
        for (int col = 0; col < MAZE_SIZE; col++) {
            printw("%c", maze[row][col]);
            printw("%c", SPACE);
        }
        printw("\n");
    }
    refresh();
}

void refresh_maze(void) {
    clear();
    refresh();
    print_maze();
}

void move_left() {
    if (person_pos.y - 1 > 0 && maze[person_pos.x][person_pos.y - 1] == SPACE) {
        struct pos current = person_pos;
        person_pos.y--;
        maze[current.x][current.y] = SPACE;
        maze[current.x][current.y - 1] = PLAYER;
        refresh_maze();
    }
}

void move_right() {
    if (person_pos.y + 1 < MAZE_SIZE && maze[person_pos.x][person_pos.y + 1] == SPACE) {
        struct pos current = person_pos;
        person_pos.y++;
        maze[current.x][current.y] = SPACE;
        maze[current.x][current.y + 1] = PLAYER;
        refresh_maze();
    }
}

void move_up() {
    if (person_pos.x - 1 > 0 && maze[person_pos.x - 1][person_pos.y] == SPACE) {
        struct pos current = person_pos;
        person_pos.x--;
        maze[current.x][current.y] = SPACE;
        maze[current.x - 1][current.y] = PLAYER;
        refresh_maze();
    }
}

void move_down() {
    if (person_pos.x + 1 < MAZE_SIZE && maze[person_pos.x + 1][person_pos.y] == SPACE) {
        struct pos current = person_pos;
        person_pos.x++;
        maze[current.x][current.y] = SPACE;
        maze[current.x + 1][current.y] = PLAYER;
        refresh_maze();
    }
}

int main() {
    initscr(); // Initialize ncurses
    raw();  // Disable line buffering
    keypad(stdscr, TRUE); // Enable function & arrow keys
    noecho();  // Don't echo input

    initialize_maze();
    print_maze();

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                move_up();
                break;
            case KEY_DOWN:
                move_down();
                break;
            case KEY_LEFT:
                move_left();
                break;
            case KEY_RIGHT:
                move_right();
                break;
            default:
                printw("\a");
                refresh();
                break;
        }
        if (person_pos.x == exit_pos.x && person_pos.y == exit_pos.y) {
            printw("Congratulations! You've reached the exit!\n");
            refresh();
            break;
        }
        refresh();
    }
    return 0;
}