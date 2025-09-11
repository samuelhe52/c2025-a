#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#define WALL '#'
#define SPACE ' '
#define PLAYER 'P'
#define BOX 'B'
#define DEST 'D'
#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8

typedef struct pos {
    int x;
    int y;
} pos;

int maze[MAZE_HEIGHT][MAZE_WIDTH] = {};
pos player_pos;
pos box_poses[5];
pos dest_poses[5];

bool is_box(const int x, const int y) {
    for (int i = 0; i < 5; i++) {
        if (box_poses[i].x == x && box_poses[i].y == y) {
            return true;
        }
    }
    return false;
}

bool is_player(const int x, const int y) {
    return player_pos.x == x && player_pos.y == y;
}

void initialize_map(void) {
    FILE *fp = fopen(LEVEL1_LAYOUT_PATH, "r");
    if (fp == NULL) {
        perror("Error opening layout file");
        exit(EXIT_FAILURE);
    }

    int box_counter = 0;
    int dest_counter = 0;
    // Fill the maze with data from file
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        char line[50] = {};
        fgets(line, 50, fp);
        for (int j = 0; j < MAZE_WIDTH; j++) {
            if (line[j] == PLAYER) {
                player_pos.y = i;
                player_pos.x = j;
            } else if (line[j] == BOX) {
                box_poses[box_counter].y = i;
                box_poses[box_counter].x = j;
                box_counter++;
            } else if (line[j] == DEST) {
                maze[i][j] = DEST;
                dest_poses[dest_counter].y = i;
                dest_poses[dest_counter].x = j;
                dest_counter++;
            } else {
                maze[i][j] = (line[j] == '1') ? WALL : SPACE;
            }
        }
    }

    fclose(fp);
}

void print_map() {
    for (int row = 0; row < MAZE_HEIGHT; row++) {
        for (int col = 0; col < MAZE_WIDTH; col++) {
            if (is_player(col, row)){
                printw("%c", PLAYER);
            } else if (is_box(col, row)) {
                printw("%c", BOX);
            } else if (maze[row][col] == DEST) {
                printw("%c", DEST);
            } else {
                printw("%c", maze[row][col]);
            }
            printw("%c", SPACE);
        }
        printw("\n");
    }
    refresh();
}

int main() {
    initscr(); // Initialize ncurses
    raw();  // Disable line buffering
    keypad(stdscr, TRUE); // Enable function & arrow keys
    noecho();  // Don't echo input

    initialize_map();
    print_map();
    return 0;
}