# Minimum CMake version
cmake_minimum_required(VERSION 2.8)

# Projects name
project(LeetCode)

# use C++11 to compile
add_compile_options(-std=c++11)

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./exhausted_search/)
set(SRC_sudoku_solver ./exhausted_search/sudoku_solver/test.cpp)
add_executable(sudoku_solver ${SRC_sudoku_solver})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./exhausted_search/)
set(SRC_combination_sum ./exhausted_search/combination_sum/test.cpp)
add_executable(combination_sum ${SRC_combination_sum})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./exhausted_search/)
set(SRC_buy_stocks ./exhausted_search/buy_stocks/test.cpp)
add_executable(buy_stocks ${SRC_buy_stocks})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./string/)
set(SRC_basic_usage ./string/basic_usage/test.cpp)
add_executable(basic_usage ${SRC_basic_usage})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_linked_list ./basic_data_structure/linked_list/test.cpp)
add_executable(linked_list ${SRC_linked_list})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_tree ./basic_data_structure/tree/test.cpp)
add_executable(tree ${SRC_tree})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_heap ./basic_data_structure/heap/test.cpp)
add_executable(heap ${SRC_heap})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_huffman_tree ./basic_data_structure/huffman_tree/test.cpp)
add_executable(huffman_tree ${SRC_huffman_tree})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_queue ./basic_data_structure/queue/test.cpp)
add_executable(queue ${SRC_queue})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_stack ./basic_data_structure/stack/test.cpp)
add_executable(stack ${SRC_stack})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_sort ./basic_data_structure/sort/test.cpp)
add_executable(sort ${SRC_sort})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_knapsack ./basic_data_structure/knapsack/test.cpp)
add_executable(knapsack ${SRC_knapsack})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_random ./basic_data_structure/random/test.cpp)
add_executable(random ${SRC_random})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_divide_conquer ./basic_data_structure/divide_conquer/test.cpp)
add_executable(divide_conquer ${SRC_divide_conquer})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_hash_table ./basic_data_structure/hash_table/test.cpp)
add_executable(hash_table ${SRC_hash_table})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_priority_queue ./basic_data_structure/priority_queue/test.cpp)
add_executable(priority_queue ${SRC_priority_queue})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./basic_data_structure/)
set(SRC_bit_set ./basic_data_structure/bit_set/test.cpp)
add_executable(bit_set ${SRC_bit_set})