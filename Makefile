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

# List of objects that are required for the linking of the final executable
OBJECTS  = SudokuGUI.o Sudoku.o

# The final executable that requires the OBJECTS list of .o files
$(BIN)/$(TARGET): clean make_directories $(OBJECTS)
	$(CC) $(CPPFLAGS) $(SRC)/$(TARGET).cpp $(OBJ)/*.o -o $(BIN)/$(TARGET).$(EXTN)

# Static Pattern Rules to create .o for all OBJECTS files
$(OBJECTS): %.o: $(SRC)/Sudoku/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $(OBJ)/$@

# Phony is not really the name of a file, rather just a recipe to be executed
.PHONY: clean make_directories
clean:
	rm -rf $(OBJ) $(BIN)

make_directories:
	mkdir -p $(OBJ) $(BIN)
