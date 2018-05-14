# Minimum CMake version
cmake_minimum_required(VERSION 2.8)

# Projects name
project(LeetCode)

# use C++11 to compile
add_compile_options(-std=c++11)

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./7_ExhaustedSearch/)
set(SRC_SudokuSolver ./ExhaustedSearch/SudokuSolver/test.cpp)
add_executable(SudokuSolver ${SRC_SudokuSolver})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./7_ExhaustedSearch/)
set(SRC_CombinationSum ./ExhaustedSearch/CombinationSum/test.cpp)
add_executable(CombinationSum ${SRC_CombinationSum})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./1_String/)
set(SRC_BasicUsage ./String/BasicUsage/test.cpp)
add_executable(BasicUsage ${SRC_BasicUsage})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./0_BasicDataStructure/)
set(SRC_LinkedList ./BasicDataStructure/LinkedList/test.cpp)
add_executable(LinkedList ${SRC_LinkedList})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./0_BasicDataStructure/)
set(SRC_Tree ./BasicDataStructure/Tree/test.cpp)
add_executable(Tree ${SRC_Tree})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./0_BasicDataStructure/)
set(SRC_Heap ./BasicDataStructure/Heap/test.cpp)
add_executable(Heap ${SRC_Heap})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./0_BasicDataStructure/)
set(SRC_HuffmanTree ./BasicDataStructure/HuffmanTree/test.cpp)
add_executable(HuffmanTree ${SRC_HuffmanTree})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./0_BasicDataStructure/)
set(SRC_Queue ./BasicDataStructure/Queue/test.cpp)
add_executable(Queue ${SRC_Queue})

# Add source files and build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./0_BasicDataStructure/)
set(SRC_PriorityQueue ./BasicDataStructure/PriorityQueue/test.cpp)
add_executable(PriorityQueue ${SRC_PriorityQueue})