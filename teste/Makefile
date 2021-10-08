# ~/Makefile

SRC_DIR := src
OBJ_DIR := obj
EXE := program
OBJ := main.o Registro.o

all: $(EXE)
clean:
	rm -rf $(EXE) $(OBJ_DIR)
.PHONY: all clean

   CXX := g++
CFLAGS := -std=c++11 -Wall -Wextra -Werror -g -Og
   OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

$(EXE): $(OBJ)
	$(CXX) -o $@ $^
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -o $@ -c $< $(CFLAGS)
$(OBJ_DIR):
	mkdir -p $@

main.o: main.cpp
