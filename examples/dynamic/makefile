CC        := g++
TARGET    := main
SOURCES   := $(shell find $(SRCDIR) -type f -name *.cpp)
CXXFLAGS  := -Wall -Wextra -Wshadow -O2
DLFLAGS   := -L../../build/shared/ -Wl,-rpath=../../build/shared/
LIB       := -lataxx
INC       := -I../../src

all: $(SOURCES)
	$(CC) $(CXXFLAGS) $(INC) $(DLFLAGS) $^ $(LIB) -o ./$(TARGET)
