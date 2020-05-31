# How to use Makefile
# 1. Create .o files for all .cpp files
# 2. Link all the .o files together with target.cpp to create the final executable

CC       = g++ -std=c++17
CPPFLAGS = -O3 -Wall -Wextra -Wpedantic -Wconversion

SRC      = src
BIN      = bin
OBJ      = $(BIN)/obj

TARGET   = Game
EXTN     = out

# The final executable that requires the OBJECTS list of .o files
$(BIN)/$(TARGET).$(EXTN): clean make_directories $(OBJ)/$(TARGET).o $(OBJ)/Sudoku.o $(OBJ)/SudokuGUI.o
	$(CC) $(CPPFLAGS) $(OBJ)/*.o -o $(BIN)/$(TARGET).$(EXTN)

# ALL the .o files that are required by the final executable
$(OBJ)/$(TARGET).o: $(SRC)/$(TARGET).cpp
	$(CC) $(CPPFLAGS) -c $(SRC)/$(TARGET).cpp -o $(OBJ)/$(TARGET).o

$(OBJ)/SudokuGUI.o: $(SRC)/SudokuGUI.cpp $(SRC)/SudokuGUI.h
	$(CC) $(CPPFLAGS) -c $(SRC)/SudokuGUI.cpp -o $(OBJ)/SudokuGUI.o

$(OBJ)/Sudoku.o: $(SRC)/Sudoku.cpp $(SRC)/Sudoku.h
	$(CC) $(CPPFLAGS) -c $(SRC)/Sudoku.cpp -o $(OBJ)/Sudoku.o

# Phony is not really the name of a file, rather just a recipe to be executed
.PHONY: clean make_directories
clean:
	rm -rf $(OBJ) $(BIN)

make_directories:
	mkdir -p $(OBJ) $(BIN)
