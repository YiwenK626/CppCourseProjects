CCFLAGS = --std=gnu++98 -pedantic -Wall -Werror -ggdb3
code: code.o
	g++ -o code $(CCFLAGS) code.o
code.o :code.cpp
	g++ -c $(CCFLAGS) code.cpp
