CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic

# Override these when SFML is installed outside pkg-config's search paths.
SFML_CFLAGS ?= $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
SFML_LIBS ?= $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

ifeq ($(strip $(SFML_LIBS)),)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
endif

ifeq ($(OS),Windows_NT)
TARGET := build/mm.exe
MKDIR := if not exist build mkdir build
else
TARGET := build/mm
MKDIR := mkdir -p build
endif

SOURCES := src/mm.cpp
HEADERS := data/graphics.hpp data/controls.hpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): Makefile $(SOURCES) $(HEADERS)
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(SFML_CFLAGS) $(SOURCES) -o $@ $(SFML_LIBS)

clean:
	$(RM) $(TARGET)
