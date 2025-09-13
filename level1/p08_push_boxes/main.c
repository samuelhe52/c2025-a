#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define WALL '#'
#define SPACE ' '
#define PLAYER 'P'
#define BOX 'B'
#define BOX_IN_PLACE 'b'
#define DEST 'D'
#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8

// x is vertical, y is horizontal
typedef struct pos {
    int x;
    int y;
} pos;

int maze[MAZE_HEIGHT][MAZE_WIDTH];
pos player_pos;
int box_count;
int dest_count;
pos box_poses[10]; // large enough for any level
pos dest_poses[10]; // large enough for any level
int step = 0;
int level = 0;
char* level_file_paths[4] = {LEVEL1_LAYOUT_PATH, LEVEL2_LAYOUT_PATH, LEVEL3_LAYOUT_PATH, LEVEL4_LAYOUT_PATH};
int player_steps[4];

void get_player_steps() {
    FILE *fp = fopen(PLAYER_STEPS_PATH, "r");
    if (fp == NULL) {
        perror("Error opening steps file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 4; i++) {
        fscanf(fp, "%d", &player_steps[i]);
    }
    fclose(fp);
}

// Returns 1 if the player has brokent the record, otherwise 0.
int set_player_steps(const int lvl, const int current_step) {
    get_player_steps();
    int broken_record = 0;
    FILE *fp = fopen(PLAYER_STEPS_PATH, "w");
    if (fp == NULL) {
        perror("Error opening steps file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 4; i++) {
        if (lvl - 1 == i && (current_step < player_steps[i] || player_steps[i] == -1)) {
            fprintf(fp, "%d\n", current_step);
            broken_record = 1;
        }
        fprintf(fp, "%d\n", player_steps[i]);
    }
    fclose(fp);
    return broken_record;
}

void initialize_map(const char* file_path) {
    FILE *fp = fopen(file_path, "r");
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

    box_count = box_counter;
    dest_count = dest_counter;

    fclose(fp);
}


int pos_equal(pos p1, pos p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

int box_in_place_count() {
    int count = 0;
    for (int i = 0; i < box_count; i++) {
        for (int j = 0; j < dest_count; j++) {
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
    for (int i = 0; i < box_count; i++) {
        if (box_poses[i].x == x && box_poses[i].y == y) {
            return i;
        }
    }
    return -1;
}

// Returns the index of a destination if a destination exists at the given location.
// Returns 0 if there's no destination.
int is_dest(const int x, const int y) {
    for (int i = 0; i < dest_count; i++) {
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

void print_map() {
    printw("Level %d\n", level);
    printw("Press 'r' to restart this level.\n");
    printw("\n");
    for (int row = 0; row < MAZE_HEIGHT; row++) {
        for (int col = 0; col < MAZE_WIDTH; col++) {
            if (is_player(row, col) != 0){
                printw("%c", PLAYER);
            } else if (is_box(row, col) != -1) {
                if (is_dest(row, col) != -1) {
                    printw("%c", BOX_IN_PLACE);
                } else {
                    printw("%c", BOX);
                }
            } else if (is_dest(row, col) != -1) {
                printw("%c", DEST);
            } else {
                printw("%c", maze[row][col]);
            }
            printw("%c", SPACE);
        }
        printw("\n");
    }
    printw("\n");
    printw("Steps: %d\n", step);
    refresh();
}

void refresh_map() {
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
        step++;
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
        step++;
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
        step++;
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
        step++;
        player_pos.x++;
        refresh_map();
    }
}

int main() {
    initscr(); // Initialize ncurses
    raw();  // Disable line buffering
    keypad(stdscr, TRUE); // Enable function & arrow keys
    noecho();  // Don't echo input

    int ch;
    while (true) {
        step = 0;
        printw("Please select a level (1-4):\n");
        refresh();
        int got_valid_level = 0;
        while (got_valid_level == 0) {
            ch = getch();
            switch (ch) {
                case '1':
                    level = 1;
                    got_valid_level = 1;
                    break;
                case '2':
                    level = 2;
                    got_valid_level = 1;
                    break;
                case '3':
                    level = 3;
                    got_valid_level = 1;
                    break;
                case '4':
                    level = 4;
                    got_valid_level = 1;
                    break;
                default:
                    printw("Please select a valid level.\n");
                    refresh();
            }
        }

        clear();

        initialize_map(level_file_paths[level - 1]);
        print_map();

        while (true) {
            ch = getch();
            if (ch == 'q') {
                endwin();
                exit(0);
            }
            if (ch == 'r') {
                initialize_map(level_file_paths[level - 1]);
                step = 0;
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
            refresh();
            if (box_in_place_count() == box_count) {
                int broken_record = set_player_steps(level, step);
                printw("Congratulations! All boxes are in place.\n");
                if (broken_record == 1) {
                    printw("And you have set a new record for this level!\n");
                }
                refresh();
                break;
            }
        }
        printw("\n");
        printw("Press 'n' to start a new game; press any other key to quit.\n");
        printw("\n");
        ch = getch();
        if (ch == 'n') continue;
        break;
    }
    endwin();
    return 0;
}