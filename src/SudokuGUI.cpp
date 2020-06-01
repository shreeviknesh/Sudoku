#include "SudokuGUI.h"

void SudokuGUI::start() {
    Sudoku game;
    game.generate_random_sudoku(Sudoku::Difficulty::Hard);
    game.print_sudoku();
    //std::cout << "\n";
    //game.solve();
    //game.print_sudoku();
}
