#include "SudokuGUI.h"
#include "Sudoku.h"

void SudokuGUI::start() const noexcept {
    Sudoku game;
    //game.generate_random_sudoku(Sudoku::Difficulty::Easy);
    game.solve();
    game.print_sudoku();
}
