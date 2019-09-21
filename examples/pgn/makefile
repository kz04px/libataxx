CC        := g++
TARGET    := main
SOURCES   := $(shell find $(SRCDIR) -type f -name *.cpp)
CXXFLAGS  := -std=c++17 -Wall -Wextra -Wshadow -O2
DLFLAGS   := -L../../build/static/
LIB       := -lataxx
INC       := -I../../src

all: $(SOURCES)
	$(CC) $(CXXFLAGS) $(INC) $(DLFLAGS) $^ $(LIB) -o ./$(TARGET)
