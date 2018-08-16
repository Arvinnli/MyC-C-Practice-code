
OBJ:=polish_notation
SRC:=$(OBJ).cpp
CC:=g++
DEBUGMACRO:=-DTRACE_INFO_SUPPORT
DEBUGARGS:=



obj:$(SRC)
	@$(CC) $(SRC) -o $(OBJ)

debugobj:$(SRC)
	@$(CC) $(SRC) -o $(OBJ) $(DEBUGMACRO)

run:obj
	@./$(OBJ)

debug:debugobj
	@./$(OBJ) $(DEBUGARGS)
	