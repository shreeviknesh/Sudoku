SRC_DIR=src
OBJ_DIR=build/objs
OUT_DIR=build
target=Game

CC=g++ -std=c++17
CPPFLAGS=-O3 -Wall

$(target): make_directories SudokuGUI.o
	$(CC) $(CPPFLAGS) $(SRC_DIR)/$(target).cpp \
		$(OBJ_DIR)/*.o -o $(OUT_DIR)/$(target).out

SudokuGUI.o: make_directories Sudoku.o SudokuSolver.o
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/SudokuGUI.cpp \
		$(OBJ_DIR)/SudokuSolver.o $(OBJ_DIR)/Sudoku.o \
		-o $(OBJ_DIR)/SudokuGUI.o

SudokuSolver.o: make_directories Sudoku.o
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/SudokuSolver.cpp \
		$(OBJ_DIR)/Sudoku.o \
		-o $(OBJ_DIR)/SudokuSolver.o

Sudoku.o: make_directories
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/Sudoku.cpp \
		-o $(OBJ_DIR)/Sudoku.o

.PHONY: clean make_directories
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

make_directories:
	mkdir -p $(OBJ_DIR) $(OUT_DIR)
