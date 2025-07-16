
# C++ compiler to use
CXX = g++

# Compiler flags:
# -Wall: Enable all standard warnings
# -Wextra: Enable extra warnings
# -std=c++17: Use C++17 standard (adjust to c++11/c++14 if string_view is an issue)
# -g: Include debugging information
# -I.: Add current directory to include paths
# $(shell pkg-config --cflags sdl2 SDL2_ttf): Get CFLAGS for SDL2 and SDL2_ttf
CXXFLAGS = -Wall -Wextra -std=c++17 -g -I. $(shell pkg-config --cflags sdl2 SDL2_ttf)

# Linker flags:
# $(shell pkg-config --libs sdl2 SDL2_ttf): Get LDFLAGS for SDL2 and SDL2_ttf
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_ttf)

# Source files
SRCS = main.cpp emu.cpp cpu.cpp bus.cpp memory.cpp cart.cpp ppu.cpp timer.cpp instructions.cpp

# Object files (generated from source files)
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = gb_emu

.PHONY: all clean

# Default target: build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile C++ source files into object files
# $<: The first prerequisite (the .cpp file)
# $@: The target (the .o file)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

