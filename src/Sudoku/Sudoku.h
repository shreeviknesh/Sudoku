#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku
{
  public:
    /* Default constructor that generates a random board */
    Sudoku();

    /* Parameterized constructor that takes the initial state of the board as
     * input*/
    Sudoku(int board[9][9]);

    /* Destructor */
    ~Sudoku() {}

    /* A function that checks if the current board configuration is valid
     * i.e., it checks if there are any repetitions in the rows/cols/box */
    [[nodiscard]] bool is_valid_configuration(const int board[9][9]) const noexcept;

    /* A function that checks if all the cells of the board are non-empty
     * and if the current configuration of the board is valid */
    [[nodiscard]] bool is_solved() const noexcept;

    /* A function that generates a random sudoku board with a fixed number of
     * clues */
    void generate_random_sudoku(const char* difficulty) noexcept;

    /* A function that prints the current state of the sudoku board to the
     * console */
    void print_sudoku() const noexcept;

  private:
    int board[9][9];
};

#endif