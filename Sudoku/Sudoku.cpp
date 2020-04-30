#include "Sudoku.h"

Sudoku::Sudoku() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			board[i][j] = 0;
		}
	}
}

Sudoku::Sudoku(int board[9][9]) {
	/* Checking if the given sudoku configuration is valid
	Throws an exception if it is invalid */
	try {
		if (!is_valid_configuration(board)) {
			throw std::exception();
		}
	}
	catch (std::exception& e) {
		std::cout << "[ERROR] Given input sudoku is invalid!" << std::endl;
		exit(69);
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			this->board[i][j] = board[i][j];
		}
	}
}

bool Sudoku::is_valid_configuration(int board[9][9]) {
	int i, j, current_val;
	std::unordered_map<int, int> seen_values;

	/* Checking all rows */
	for (i = 0; i < 9; i++) {
		seen_values.clear();

		for (j = 0; j < 9; j++) {
			current_val = board[i][j];

			/* Checking if any invalid values exist in the board */
			if (current_val > 9 || current_val < 0) {
				return false;
			}
			else if (current_val == 0) {
				continue;
			}
			else {
				if (seen_values[current_val] == 0) {
					seen_values[current_val] = 1;
				}
				else {
					return false;
				}
			}
		}
	}

	/* Checking all columns */
	for (j = 0; j < 9; j++) {
		seen_values.clear();

		for (i = 0; i < 9; i++) {
			current_val = board[i][j];
			if (current_val == 0) {
				continue;
			}
			if (seen_values[current_val] == 0) {
				seen_values[current_val] = 1;
			}
			else {
				return false;
			}
		}
	}

	/* Checking all boxes */
	for (int rows = 3; rows <= 9; rows += 3) {
		for (int cols = 3; cols <= 9; cols += 3) {

			for (i = rows - 3; i < rows; i++) {
				seen_values.clear();

				for (j = cols - 3; j < cols; j++) {
					current_val = board[i][j];
					if (current_val == 0) {
						continue;
					}
					if (seen_values[current_val] == 0) {
						seen_values[current_val] = 1;
					}
					else {
						return false;
					}
				}
			}
		}
	}

	/* It is a valid configuration */
	return true;
}

bool Sudoku::is_solved() {
	/* Checking if the board contains any empty tile */
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}

	/* If there are no empty tiles, checking if the board is valid */
	return is_valid_configuration(this->board);
}

void Sudoku::generate_random_sudoku(const char* difficulty) {

}

void Sudoku::print_sudoku() {
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0 && i != 0) {
			std::cout << "- - - - - - - - - - -" << std::endl;
		}
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0 && j != 0) {
				std::cout << "| ";
			}
			if (board[i][j] == 0) {
				std::cout << "  ";
			}
			else {
				std::cout << board[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
}