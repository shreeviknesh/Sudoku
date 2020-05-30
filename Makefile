SRC_DIR   = src
OBJ_DIR   = bin/obj
OUT_DIR   = bin
target    = Game
extension = out
CC        = g++ -std=c++17
CPPFLAGS  = -O3 -Wall

$(OUT_DIR)/$(target): clean make_directories $(OBJ_DIR)/Sudoku.o $(OBJ_DIR)/SudokuGUI.o $(OBJ_DIR)/SudokuSolver.o
	$(CC) $(CPPFLAGS) $(SRC_DIR)/$(target).cpp $(OBJ_DIR)/*.o -o $(OUT_DIR)/$(target).$(extension)

$(OBJ_DIR)/SudokuGUI.o: $(SRC_DIR)/Sudoku/SudokuGUI.cpp
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/SudokuGUI.cpp -o $(OBJ_DIR)/SudokuGUI.o

$(OBJ_DIR)/SudokuSolver.o: $(SRC_DIR)/Sudoku/SudokuSolver.cpp
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/SudokuSolver.cpp -o $(OBJ_DIR)/SudokuSolver.o

$(OBJ_DIR)/Sudoku.o: $(SRC_DIR)/Sudoku/Sudoku.cpp
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Sudoku/Sudoku.cpp -o $(OBJ_DIR)/Sudoku.o

.PHONY: clean make_directories
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

make_directories:
	mkdir -p $(OBJ_DIR) $(OUT_DIR)
