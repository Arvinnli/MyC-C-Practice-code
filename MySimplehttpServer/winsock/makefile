
src = server.cpp
src1 = client.cpp
obj = server
obj1 = client
CC = g++

lib = -lws2_32

all:
		@$(CC) $(src) -o $(obj) $(lib)
		@$(CC) $(src1) -o $(obj1) $(lib)

clean:
ifeq ($(obj).exe, $(wildcard $(obj).exe))
		@rm $(obj).exe
endif
ifeq ($(obj1).exe, $(wildcard $(obj1).exe))
		@rm $(obj1).exe
endif