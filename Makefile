CC       = g++ -std=c++17
CPPFLAGS = -O3 -Wall -Wextra -Wpedantic -Wconversion

SRC      = src
BIN      = bin
OBJ      = $(BIN)/obj
TARGET   = Game
EXTN     = out

$(BIN)/$(TARGET): clean make_directories $(OBJ)/Sudoku.o $(OBJ)/SudokuGUI.o $(OBJ)/SudokuSolver.o
	$(CC) $(CPPFLAGS) $(SRC)/$(TARGET).cpp $(OBJ)/*.o -o $(BIN)/$(TARGET).$(EXTN)

$(OBJ)/SudokuGUI.o: $(SRC)/Sudoku/SudokuGUI.cpp
	$(CC) $(CPPFLAGS) -c $(SRC)/Sudoku/SudokuGUI.cpp -o $(OBJ)/SudokuGUI.o

$(OBJ)/SudokuSolver.o: $(SRC)/Sudoku/SudokuSolver.cpp
	$(CC) $(CPPFLAGS) -c $(SRC)/Sudoku/SudokuSolver.cpp -o $(OBJ)/SudokuSolver.o

$(OBJ)/Sudoku.o: $(SRC)/Sudoku/Sudoku.cpp
	$(CC) $(CPPFLAGS) -c $(SRC)/Sudoku/Sudoku.cpp -o $(OBJ)/Sudoku.o

.PHONY: clean make_directories
clean:
	rm -rf $(OBJ) $(BIN)

make_directories:
	mkdir -p $(OBJ) $(BIN)
