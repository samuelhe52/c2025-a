#include <printf.h>
#include <stdlib.h>

const char poles[3] = {'A', 'B', 'C'};

void hanoi_move(char src, char dst, int count) {
    if (count == 1) {
        printf("%c -> %c\n", src, dst);
        return;
    }

    char free_pole;
    for (int i = 0; i < 3; i++) {
        if (!(poles[i] == src || poles[i] == dst)) {
            free_pole = poles[i];
        }
    }

    hanoi_move(src, free_pole, count - 1);
    hanoi_move(src, dst, 1);
    hanoi_move(free_pole, dst, count - 1);
}

int main() {
    hanoi_move('A', 'C', 4);
    return 0;
}