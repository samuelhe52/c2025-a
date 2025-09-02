#include <printf.h>
#include <tgmath.h>
#include <stdbool.h>

bool is_prime(const int n) {
    // Test up to the square root of n
    int maximum_try_num = sqrt(n);
    for (int i = 2; i <= maximum_try_num; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num;
    scanf("%d",&num);
    printf("%d %s a prime number.", num, is_prime(num) ? "is" : "is not");
    return 0;
}