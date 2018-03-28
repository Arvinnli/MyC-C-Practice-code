

# STD = -std=c++11
STD = 
OBJ = test
DEBUG_OBJ = 
CC = gcc
SRC = test.c leptjson.c
FLAG = 
DEBUG_FLAG = 
LIB = 

obj:$(SRC)
		@$(CC) $(STD) $(SRC) -o $(OBJ) $(LIB)

debug:$(SRC)
		@$(CC) $(STD) $(SRC) -o $(OBJ) $(DEBUG_FLAG) $(LIB)

run:
ifeq ($(OBJ).exe, $(wildcard $(OBJ).exe))
		@./$(OBJ).exe
endif

clean:
ifeq ($(OBJ).exe, $(wildcard $(OBJ).exe))
		@rm $(OBJ).exe
endif