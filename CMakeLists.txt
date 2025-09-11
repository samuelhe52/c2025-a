cmake_minimum_required(VERSION 4.0)
project(c2025_challenge)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(p00_level0_bubble_sort level0/bubbleSort/main.c)

add_executable(p00_level0_all_assignments level0/main.c)

add_executable(p01_running_letter level1/p01_running_letter/main.c)

add_executable(p02_is_prime  level1/p02_is_prime/main.c)

add_executable(p03_all_primes  level1/p03_all_primes/main.c)

add_executable(p04_goldbach  level1/p04_goldbach/main.c)

add_executable(p05_encrypt_decrypt  level1/p05_encrypt_decrypt/main.c)

target_link_libraries(p05_encrypt_decrypt PRIVATE OpenSSL::Crypto)

add_executable(p06_hanoi  level1/p06_hanoi/main.c)

add_executable(p07_maze  level1/p07_maze/main.c)

target_compile_definitions(p07_maze PRIVATE
        LAYOUT_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/level1/p07_maze/maze_layout.txt"
)

target_link_libraries(p07_maze PRIVATE ${CURSES_LIBRARIES})

add_executable(p08_push_boxes  level1/p08_push_boxes/main.c)

target_compile_definitions(p08_push_boxes PRIVATE
        LEVEL1_LAYOUT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/level1/p08_push_boxes/layout_level_1.txt"
)

target_link_libraries(p08_push_boxes PRIVATE ${CURSES_LIBRARIES})

add_executable(p09_linked_list  level1/p09_linked_list/main.c)

add_executable(p10_warehouse  level1/p10_warehouse/main.c)
