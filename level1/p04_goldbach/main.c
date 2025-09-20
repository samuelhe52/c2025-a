#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// The Goldbach Conjecture states that every even integer greater than 2
// is the sum of two prime numbers.
// For example, 4 = 2 + 2, 6 = 3 + 3, 8 = 3 + 5, 10 = 3 + 7, and so on.

// Task: prove its correctness under 100.

bool is_prime(const int n) {
    const int max_try_num = (int)sqrt(n);
    for (int try_num = 2; try_num <= max_try_num; try_num++) {
        if (n % try_num == 0) {
            return false;
        }
    }
    return true;
}

bool goldbach(int n) {
    for (int i = 2; i <= n / 2; i++) {
        if (is_prime(i) && is_prime(n - i)) {
            return true;
        }
    }
    return false;
}


int main() {
    const int max_num = 10000000;

    struct timespec start, end;
    timespec_get(&start, TIME_UTC);
    for (int i = 4; i < max_num; i += 2) {
        if (!goldbach(i)) {
            printf("Failed, num: %d", i);
            return 1;
        }
    }
    timespec_get(&end, TIME_UTC);
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    if (nanoseconds < 0) {
        seconds -= 1;
        nanoseconds += 1000000000L;
    }
    long total_ns = seconds * 1000000000L + nanoseconds;
    printf("Time taken: %ld ms.\n", total_ns / 1000000);
    printf("Passed");

    return 0;
}