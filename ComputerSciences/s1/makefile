

STD = 
OBJ = test
DEBUG_OBJ = 
CC = gcc
SRC = test.c
FLAG = 
# INTELASM = -masm=intel
# INTELASM = -masm=att
INTELASM = 

DEBUG_FLAG = -DTRACE_INFO_SUPPORT
LIB = -lws2_32

asm:$(SRC)
		$(CC) $(INTELASM) -S $(SRC) -o  $(OBJ).asm
		

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