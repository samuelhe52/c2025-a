#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <tgmath.h>
#include <stdarg.h>

void print_int_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void assignment_0() {
    printf("Hello world! I'm 何子谦\n");
}

void assignment_1_1(int num) {
    if (num > 0) {
        printf("%d is a positive number.\n", num);
    } else if (num < 0) {
        printf("%d is a negative number.\n", num);
    } else {
        printf("0!\n");
    }

    if (num % 13 == 0) {
        printf("%d is a multiple of 13.\n", num);
    }
}

void assignment_1_2(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }
}

// Returns the largest number.
int assignment_1_4(int nums[], int size) {
    int largest = nums[0];
    for (int i = 1; i < size; i++) {
        if (nums[i] > largest) {
            largest = nums[i];
        }
    }
    return largest;
}

void assignment_2_1() {
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0 || (i % 10) == 7) {
            printf("%d passed.\n", i);
        }
    }
}

void assignment_2_2() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            printf("%d x %d = %d;\t",i, j, i * j);
        }
        printf("\n");
    }
}

void reverse_array(int arr[], int count) {
    int start = 0;
    int end = count - 1;
    while (start < end) {
        int temp = arr[end];
        arr[end] = arr[start];
        arr[start] = temp;

        start++;
        end--;
    }
}

void assignment_2_3(int count, ...) {
    va_list args;
    va_start(args, count);
    int args_arr[count];
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        args_arr[i] = value;
    }

    reverse_array(args_arr, count);

    for (int i = 0; i < count; i++) {
        printf("%d ", args_arr[i]);
    }
}

void assignment_2_4(int num1, int num2, int num3, int num4, int num5) {
    for (int i = 0; i < 10; i++) {
        if (!(num1 == i || num2 == i || num3 == i || num4 == i || num5 == i)) {
            printf("%d ", i);
        }
    }
}

// Bucket sort the array in place.
// void assignment_2_5(int nums[], int size) {
//     const int min_value = 0;
//     const int max_value = 99;
//     const int bucket_size = 10;
//     const int bucket_count = 10;
//     int buckets[bucket_count][bucket_size];
//     for (int i = 0; i < size; i++) {
//         int bucket_index = nums[i] / bucket_size;
//         buckets[bucket_index][]
//     }
// }

int sum_of_arrays(int nums[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += nums[i];
    }
    return result;
}

int factorial(int num) {
    if (num == 0) {
        return 1;
    }

    for (int i = 1; i <= num; i++) {
        num *= i;
    }

    return num;
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

bool is_right_triangle(int n1, int n2, int n3) {
    int arr[3] = {n1, n2, n3};

    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (arr[j] >= arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int leg1 = arr[0];
    int leg2 = arr[1];
    int hypo = arr[2];

    if ((leg1 * leg1 + leg2 * leg2) == (hypo * hypo)) {
        return true;
    }
    return false;
}

typedef struct Rect {
    int x;
    int y;
    int width;
    int height;
}rect_t;

bool check_overlap(rect_t rect1, rect_t rect2) {
    // 1. Check horizontal
    if (rect1.x + rect1.width < rect2.x || rect2.x + rect2.width < rect1.x) {
        return false;
    }

    if (rect1.y + rect1.height < rect2.y || rect2.y + rect2.height < rect1.y) {
        return false;
    }

    return true;
}

void test_check_overlap() {
    rect_t r1 = {0, 0, 10, 10};
    rect_t r2 = {5, 5, 10, 10}; // Overlapping
    rect_t r3 = {10, 10, 5, 5}; // Touching at corner
    rect_t r4 = {11, 11, 5, 5}; // Not overlapping
    rect_t r5 = {0, 0, 10, 10}; // Identical to r1
    rect_t r6 = {2, 2, 5, 5};   // Contained within r1
    rect_t r7 = {0, 10, 10, 5}; // Touching at edge

    printf("%s", check_overlap(r1, r4) ? "true" : "false");
}

double usd_to_cny(double n) {
    const double rate = 7.13;
    return n * rate;
}

int main() {
    test_check_overlap();
    return 0;
}
