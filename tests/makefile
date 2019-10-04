CC       = g++
CFLAGS   = -std=c++17 -O2 -Wall -Wextra -Wshadow
INC      = -I../src/
DLFLAGS  = -L../build/static/
LFLAGS   = -pthread -lboost_system -lataxx

all:
	$(CC) $(CFLAGS) $(INC) *.cpp $(DLFLAGS) $(LFLAGS) -o main

.PHONY: clean
