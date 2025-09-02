#include <printf.h>
#include <stdlib.h>
#include <unistd.h>


#define LETTER "A"
#define SPACE " "
#define WIDTH 50

void clear_console() {
    system("clear");
    fflush(stdout);
}

int main() {
    int position = 0;
    int direction = 1; // 1 for forwards, -1 for backwards.

    while (1) {
        clear_console();

        for (int i = 1; i <= position; i++) {
            printf(SPACE);
        }
        printf(LETTER);
        fflush(stdout);
        usleep(80000);

        position += direction;

        if (position >= WIDTH || position == 0) {
            direction *= -1;
        }
    }
}