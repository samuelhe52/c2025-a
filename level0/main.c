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

// Bubble sorts the array in place.
void assignment_1_5(int nums[], int size) {
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (nums[j] > nums[j + 1]) {
                const int temp = nums[j + 1];
                nums[j + 1] = nums[j];
                nums[j] = temp;
            }
        }
    }
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

int main() {
    assignment_2_4(1,2,3,4,5);
    return 0;
}