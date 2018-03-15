src = http.cpp
src1 = myweb.cpp
CC = g++
obj = http
obj1 = myweb
macro = -D__WIN32

lib = -lws2_32



all:
		@$(CC) $(src) -o $(obj) $(macro) $(lib)



myweb:
		@$(CC) $(src1) -o $(obj1) $(macro) $(lib)

debug:
		@$(CC) $(src1) -o $(obj1) $(macro) $(lib) -DTRACE_INFO_SUPPORT