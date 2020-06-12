#include "Sudoku.h"
#include <cstdint>
#include <limits>

Sudoku::Sudoku(const uint8_t (&board)[9][9]) {
    /* Checking if the given sudoku configuration is valid
     * Prints an error if it is invalid */
    try {
        if (!is_valid_configuration()) {
            throw std::exception();
        }
        std::memcpy(this->board, board, sizeof(board[0][0]) * 81);
    } catch (const std::exception&) {
        std::cout << "\033[31m[ERROR] \033[0m"
                  << "Given input sudoku is invalid!" << '\n';
    }
}

[[nodiscard]] bool Sudoku::is_valid_configuration() const noexcept {
    std::unordered_set<uint8_t> seen_values;

    /* Checking all rows */
    for (size_t i = 0; i < 9; i++) {
        seen_values.clear();
        for (size_t j = 0; j < 9; j++) {
            uint8_t current_val = board[i][j];

            /* Checking if any invalid values exist in the board */
            if (current_val > 9) {
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
    for (size_t j = 0; j < 9; j++) {
        seen_values.clear();
        for (size_t i = 0; i < 9; i++) {
            uint8_t current_val = board[i][j];

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
    for (size_t rows = 0; rows < 9; rows += 3) {
        for (size_t cols = 0; cols < 9; cols += 3) {
            seen_values.clear();
            for (size_t i = rows; i < rows + 3; i++) {
                for (size_t j = cols; j < cols + 3; j++) {
                    uint8_t current_val = board[i][j];
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

[[nodiscard]] std::pair<size_t, size_t> Sudoku::get_first_empty() const noexcept {
    /* Checking if the board contains any empty tile */
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(std::numeric_limits<size_t>::max(), 0);
}

[[nodiscard]] bool Sudoku::is_solved() const noexcept {
    /* Checking if there are any empty cells */
    auto [row, col] = get_first_empty();
    if (row != std::numeric_limits<size_t>::max()) {
        return false;
    }
    /* If there are no empty tiles, checking if the board is valid */
    return is_valid_configuration();
}

void Sudoku::generate_random_sudoku(Sudoku::Difficulty diff) noexcept {
    int num_correct;
    switch (diff) {
    case Difficulty::Easy:
        num_correct = 45;
        break;
    case Difficulty::Medium:
        num_correct = 35;
        break;
    case Difficulty::Hard:
        num_correct = 25;
        break;
    default:
        num_correct = 23;
    }

    if (!solve()) {
        std::cout << "\033[31m[ERROR] \033[0m"
                  << "Couldn't generate sudoku" << '\n';
        return;
    }

    srand(static_cast<uint32_t>(std::time(nullptr)));
    int to_delete = 81 - num_correct;
    int deleted = 0;

    while (deleted < to_delete) {
        size_t row = rand() % 9;
        size_t col = rand() % 9;

        if (board[row][col] != 0) {
            board[row][col] = 0;
            deleted++;
        }
    }
}

bool Sudoku::solve() noexcept {
    auto [row, col] = get_first_empty();
    if (row == std::numeric_limits<size_t>::max()) {
        return true;
    }

    std::array<uint8_t, 9> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(static_cast<uint32_t>(std::time(nullptr))));
    for (uint8_t num : nums) {
        board[row][col] = num;
        if (is_valid_configuration() && solve()) {
            return true;
        }
        board[row][col] = 0;
    }

    return false;
}

void Sudoku::print_sudoku() const noexcept {
    for (size_t i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "---------------------" << '\n';
        }
        for (size_t j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }
            if (board[i][j] == 0) {
                std::cout << "  ";
            } else {
                std::cout << static_cast<uint32_t>(board[i][j]) << " ";
            }
        }
        std::cout << '\n';
    }
}
