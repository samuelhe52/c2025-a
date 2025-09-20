#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define PRIME_TABLE_SIZE 5001

// I decided to count the number of primes from 2-5000, since 1000 is too small,
// and printing all of them makes the difference negligible.

bool is_prime(const int n) {
    // Test up to the square root of n
    const int maximum_try_num = sqrt(n);
    for (int i = 2; i <= maximum_try_num; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void find_all_primes_simplest() {
    int counter = 0;

    for (int n = 2; n < PRIME_TABLE_SIZE; n++) {
        if (is_prime(n)) {
            counter++;
        }
    }

    printf("%d\n", counter);
}

void find_all_primes_optimized_old() {
    int prime_table[PRIME_TABLE_SIZE] = {}; // 0 for prime, 1 for non-prime
    prime_table[0] = 1;
    prime_table[1] = 1;

    const int max_try_num = sqrt(PRIME_TABLE_SIZE - 1);
    for (int n = 2; n <= max_try_num; n++) {
        if (is_prime(n)) {
            int x = 1;
            while (1) {
                x++;
                if (x * n < PRIME_TABLE_SIZE) {
                    prime_table[x * n] = 1;
                } else {
                    break;
                }
            }
        }
    }

    int counter = 0;

    for (int i = 2; i < PRIME_TABLE_SIZE; i++) {
        if (prime_table[i] == 0) {
            counter++;
        }
    }

    printf("%d\n", counter);
}

// Inspired by AI 🤔, no need to use is_prime() check.
void find_all_primes_optimized() {
    int prime_table[PRIME_TABLE_SIZE] = {}; // 0 for prime, 1 for non-prime
    prime_table[0] = 1;
    prime_table[1] = 1;

    const int max_try_num = sqrt(PRIME_TABLE_SIZE - 1);
    for (int n = 2; n <= max_try_num; n++) {
        if (prime_table[n] == 0) {
            for (int x = n; x * n < PRIME_TABLE_SIZE; x++) {
                prime_table[x * n] = 1;
            }
        }
    }

    int counter = 0;

    for (int i = 2; i < PRIME_TABLE_SIZE; i++) {
        if (prime_table[i] == 0) {
            counter++;
        }
    }

    printf("%d\n", counter);
}

struct prime_array {
    int size;
    int primes[]; // flexible array member
};

struct prime_array* find_all_primes(const int max_num) {
    if (max_num < 2) {
        struct prime_array* empty = malloc(sizeof(struct prime_array));
        empty->size = 0;
        return empty;
    }

    int* sieve = calloc(max_num, sizeof(int)); // 0 = prime, 1 = not prime
    sieve[0] = sieve[1] = 1;

    const int limit = (int)sqrt(max_num - 1);
    for (int n = 2; n <= limit; n++) {
        if (sieve[n] == 0) {
            for (int multiple = n * n; multiple < max_num; multiple += n) {
                sieve[multiple] = 1;
            }
        }
    }

    int count = 0;
    for (int i = 2; i < max_num; i++) {
        if (sieve[i] == 0) count++;
    }

    struct prime_array* result = malloc(sizeof(struct prime_array) + count * sizeof(int));
    result->size = count;

    int idx = 0;
    for (int i = 2; i < max_num; i++) {
        if (sieve[i] == 0) {
            result->primes[idx++] = i;
        }
    }

    free(sieve);
    return result;
}

int main() {
    struct timespec start, end;
    timespec_get(&start, TIME_UTC);
    printf("Prime number count: ");
    find_all_primes_optimized_old(); // ~45000 ns
    find_all_primes_optimized(); // ~42000 ns
    // find_all_primes_simplest(); // ~125000 ns
    // Both counts to 669 primes.
    timespec_get(&end, TIME_UTC);
    printf("Time taken: %ld ns.", (end.tv_nsec - start.tv_nsec));
    return 0;
}