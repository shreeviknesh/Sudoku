SRC_DIR=src
OBJ_DIR=build/objs
OUT_DIR=build
target=SudokuGUI

CC=g++ -std=c++17
CPPFLAGS=-O3 -Wall

$(target): Sudoku.o SudokuSolver.o make_directories
	$(CC) $(CPPFLAGS) $(SRC_DIR)/SudokuGUI/SudokuGUI.cpp $(OBJ_DIR)/*.o -o $(OUT_DIR)/SudokuGUI.out

Sudoku.o: make_directories
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/Sudoku.cpp -o $(OBJ_DIR)/Sudoku.o

SudokuSolver.o: make_directories
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/SudokuSolver.cpp -o $(OBJ_DIR)/SudokuSolver.o

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

.PHONY: make_directories
make_directories:
	mkdir -p $(OBJ_DIR) $(OUT_DIR)
