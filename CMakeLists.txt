cmake_minimum_required(VERSION 3.15)
project(Sudoku
    VERSION 1.0
    DESCRIPTION "A Sudoku GUI"
    LANGUAGES CXX
    )
set(CMAKE_CXX_STANDARD 17)
add_executable(
    SudokuGUI
    SudokuGUI/SudokuGUI.cpp
    )
