# Minimum CMake version
cmake_minimum_required(VERSION 2.8)

# Projects name
project(LeetCode)

# use C++11 to compile
add_compile_options(-std=c++11)

# Add source files and build
set(SRC_SudokuSolver ./SudokuSolver/test.cpp)
add_executable(SudokuSolver ${SRC_SudokuSolver})

# Add source files and build
set(SRC_CombinationSum ./CombinationSum/test.cpp)
add_executable(CombinationSum ${SRC_CombinationSum})