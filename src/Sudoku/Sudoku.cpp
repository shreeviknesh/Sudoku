#include "Sudoku.h"

#include <iostream>
#include <unordered_set>
#include <array>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

Sudoku::Sudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }
}

Sudoku::Sudoku(int board[9][9]) {
    /* Checking if the given sudoku configuration is valid
     * Throws an exception if it is invalid */
    try {
        if (!is_valid_configuration()) {
            throw std::exception();
        }
    } catch (const std::exception&) {
        std::cout << "\033[31m[ERROR] \033[0m"
                  << "Given input sudoku is invalid!" << std::endl;
        exit(69);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}

[[nodiscard]] bool Sudoku::is_valid_configuration() const noexcept {
    std::unordered_set<int> seen_values;
    /* Checking all rows */
    for (int i = 0; i < 9; i++) {
        seen_values.clear();
        for (int j = 0; j < 9; j++) {
            int current_val = board[i][j];

            /* Checking if any invalid values exist in the board */
            if (current_val > 9 || current_val < 0) {
                return false;
            } else if (current_val == 0) {
                continue;
            } else {
                if (seen_values.find(current_val) == seen_values.end()) {
                    seen_values.insert(current_val);
                } else {
                    return false;
                }
            }
        }
    }

    /* Checking all columns */
    for (int j = 0; j < 9; j++) {
        seen_values.clear();

        for (int i = 0; i < 9; i++) {
            int current_val = board[i][j];

            if (current_val == 0) {
                continue;
            } else {
                if (seen_values.find(current_val) == seen_values.end()) {
                    seen_values.insert(current_val);
                } else {
                    return false;
                }
            }
        }
    }

    /* Checking all boxes */
    for (int rows = 0; rows < 9; rows += 3) {
        for (int cols = 0; cols < 9; cols += 3) {
            seen_values.clear();
            for (int i = rows; i < rows + 3; i++) {
                for (int j = cols; j < cols + 3; j++) {
                    int current_val = board[i][j];
                    if (current_val == 0) {
                        continue;
                    }
                    if (seen_values.find(current_val) == seen_values.end()) {
                        seen_values.insert(current_val);
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    /* It is a valid configuration */
    return true;
}

[[nodiscard]] std::pair<int, int> Sudoku::get_first_empty() const noexcept {
    /* Checking if the board contains any empty tile */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

[[nodiscard]] bool Sudoku::is_solved() const noexcept {
    auto [row, col] = get_first_empty();
    if (row != -1 && col != -1) {
        return false;
    }
    /* If there are no empty tiles, checking if the board is valid */
    return is_valid_configuration();
}

void Sudoku::generate_random_sudoku(Sudoku::Difficulty diff) noexcept {
    int num_correct = 0;

    switch (diff) {
    case Difficulty::Easy:
        num_correct = 40;
        break;
    case Difficulty::Medium:
        num_correct = 30;
        break;
    case Difficulty::Hard:
        num_correct = 25;
        break;
    default:
        num_correct = 18;
    }

    if (!solve()) {
        std::cout << "\033[31m[ERROR] \033[0m"
                  << "Couldn't generate sudoku" << std::endl;
        exit(69);
    }

    srand(static_cast<unsigned int>(std::time(nullptr)));
    int to_delete = 81 - num_correct;
    int deleted = 0;

    while (deleted < to_delete) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (board[row][col] != 0) {
            board[row][col] = 0;
            deleted++;

            //if (solve()) {
            //deleted++;
            //} else {
            //board[row][col] = temp;
            //}
        }
    }
}

bool Sudoku::solve() noexcept {
    auto [row, col] = get_first_empty();
    if (row == -1 && col == -1) {
        return true;
    }

    std::array<int, 9> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(static_cast<unsigned int>(std::time(nullptr))));
    for (int num : nums) {
        board[row][col] = num;
        if (is_valid_configuration()) {
            if (solve()) {
                return true;
            }
        }
        board[row][col] = 0;
    }

    return false;
}

void Sudoku::print_sudoku() const noexcept {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "---------------------" << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }
            if (board[i][j] == 0) {
                std::cout << "  ";
            } else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}
