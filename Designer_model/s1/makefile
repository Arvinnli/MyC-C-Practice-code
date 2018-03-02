

STD = -std=c++11
OBJ = test
DEBUG_OBJ = 
CC = g++
SRC = test.cpp
FLAG = 
DEBUG_FLAG = -DTRACE_INFO_SUPPORT

obj:$(SRC)
		@$(CC) $(STD) $(SRC) -o $(OBJ)

debug:$(SRC)
		@$(CC) $(STD) $(SRC) -o $(OBJ) $(DEBUG_FLAG)

run:
ifeq ($(OBJ).exe, $(wildcard $(OBJ).exe))
		@./$(OBJ).exe
endif

clean:
ifeq ($(OBJ).exe, $(wildcard $(OBJ).exe))
		@rm $(OBJ).exe
endif