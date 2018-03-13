

STD = -std=c++11
OBJ = test
DEBUG_OBJ = 
CC = g++
SRC = test.cpp
FLAG = 
DEBUG_FLAG = -DTRACE_INFO_SUPPORT
LIB = -lws2_32
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