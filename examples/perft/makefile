CC        := g++
TARGET    := main
SOURCES   := $(shell find $(SRCDIR) -type f -name *.cpp)
CXXFLAGS  := -Wall -Wextra -Wshadow -O2
DLFLAGS   := -L../../build/static/
LIB       := -lataxx
INC       := -I../../src/include

all: $(SOURCES)
	$(CC) $(CXXFLAGS) $(INC) $(DLFLAGS) $^ $(LIB) -o ./$(TARGET)
