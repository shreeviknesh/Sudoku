#ifndef SUDOKU_H
#define SUDOKU_H
class Sudoku
{
  private:
    int board[9][9];

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
    bool is_valid_configuration(int board[9][9]);

    /* A function that checks if all the cells of the board are non-empty
     * and if the current configuration of the board is valid */
    bool is_solved();

    /* A function that generates a random sudoku board with a fixed number of
     * clues */
    void generate_random_sudoku(const char* difficulty);

    /* A function that prints the current state of the sudoku board to the
     * console */
    void print_sudoku();
};

#endif
