#include <stdlib.h>
#include <ncurses.h>

#define WALL '#'
#define SPACE ' '
#define PLAYER 'P'
#define BOX 'B'
#define DEST 'D'
#define BOX_COUNT 6
#define DEST_COUNT 6
#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8

// x is vertical, y is horizontal
typedef struct pos {
    int x;
    int y;
} pos;

int maze[MAZE_HEIGHT][MAZE_WIDTH] = {};
pos player_pos;
pos box_poses[BOX_COUNT];
pos dest_poses[DEST_COUNT];

int pos_equal(pos p1, pos p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

int box_in_place_count() {
    int count = 0;
    for (int i = 0; i < BOX_COUNT; i++) {
        for (int j = 0; j < DEST_COUNT; j++) {
            if (pos_equal(box_poses[i], dest_poses[j])) {
                count++;
            }
        }
    }
    return count;
}

// Returns the index of a box if a box exists at the given location.
// Returns -1 if there's no box.
int is_box(const int x, const int y) {
    for (int i = 0; i < BOX_COUNT; i++) {
        if (box_poses[i].x == x && box_poses[i].y == y) {
            return i;
        }
    }
    return -1;
}

// Returns the index of a destination if a destination exists at the given location.
// Returns 0 if there's no destination.
int is_dest(const int x, const int y) {
    for (int i = 0; i < DEST_COUNT; i++) {
        if (dest_poses[i].x == x && dest_poses[i].y == y) {
            return i;
        }
    }
    return -1;
}

// Returns 1 if the given location is the player's position, otherwise returns 0.
int is_player(const int x, const int y) {
    return player_pos.x == x && player_pos.y == y;
}

int is_wall(const int x, const int y) {
    return maze[x][y] == WALL;
}

void initialize_map(void) {
    FILE *fp = fopen(LEVEL4_LAYOUT_PATH, "r");
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
                player_pos.x = i;
                player_pos.y = j;
            } else if (line[j] == BOX) {
                box_poses[box_counter].x = i;
                box_poses[box_counter].y = j;
                box_counter++;
            } else if (line[j] == DEST) {
                dest_poses[dest_counter].x = i;
                dest_poses[dest_counter].y = j;
                dest_counter++;
            }
            maze[i][j] = (line[j] == '1') ? WALL : SPACE;
        }
    }

    fclose(fp);
}

void print_map() {
    for (int row = 0; row < MAZE_HEIGHT; row++) {
        for (int col = 0; col < MAZE_WIDTH; col++) {
            if (is_player(row, col) != 0){
                printw("%c", PLAYER);
            } else if (is_box(row, col) != -1) {
                printw("%c", BOX);
            } else if (is_dest(row, col) != -1) {
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

void refresh_map(void) {
    clear();
    refresh();
    print_map();
}

void move_left() {
    if (!is_wall(player_pos.x, player_pos.y - 1)) {
        const int idx = is_box(player_pos.x, player_pos.y - 1);
        if (idx != -1) {
            if (is_wall(player_pos.x, player_pos.y - 2) ||
                is_box(player_pos.x, player_pos.y - 2) != -1) return;
            box_poses[idx].y--;
        }
        player_pos.y--;
        refresh_map();
    }
}

void move_right() {
    if (!is_wall(player_pos.x, player_pos.y + 1)) {
        const int idx = is_box(player_pos.x, player_pos.y + 1);
        if (idx != -1) {
            if (is_wall(player_pos.x, player_pos.y + 2) ||
                is_box(player_pos.x, player_pos.y + 2) != -1) return;
            box_poses[idx].y++;
        }
        player_pos.y++;
        refresh_map();
    }
}

void move_up() {
    if (!is_wall(player_pos.x - 1, player_pos.y)) {
        const int idx = is_box(player_pos.x - 1, player_pos.y);
        if (idx != -1) {
            if (is_wall(player_pos.x - 2, player_pos.y) ||
                is_box(player_pos.x - 2, player_pos.y) != -1) return;
            box_poses[idx].x--;
        }
        player_pos.x--;
        refresh_map();
    }
}

void move_down() {
    if (!is_wall(player_pos.x + 1, player_pos.y)) {
        const int idx = is_box(player_pos.x + 1, player_pos.y);
        if (idx != -1) {
            if (is_wall(player_pos.x + 2, player_pos.y) ||
                is_box(player_pos.x + 2, player_pos.y) != -1) return;
            box_poses[idx].x++;
        }
        player_pos.x++;
        refresh_map();
    }
}

int main() {
    initscr(); // Initialize ncurses
    raw();  // Disable line buffering
    keypad(stdscr, TRUE); // Enable function & arrow keys
    noecho();  // Don't echo input

    initialize_map();
    print_map();

    int ch;
    while ((ch = getch()) != 'q') {
        if (ch == 'r') {
            initialize_map();
            refresh_map();
            continue;
        }
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
        if (box_in_place_count() == BOX_COUNT) {
            printw("Congratulations! All boxes are in place now!\n");
            refresh();
            break;
        }
        refresh();
    }

    return 0;
}