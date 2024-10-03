# Makefile

# Compiler
CXX ?= g++

CXXFLAGS = --std=c++17 -Wall -Werror -g

CXXLIBS = -lGL -lsfml-graphics -lsfml-window -lsfml-system

main: main.cpp
	$(CXX) $(CXXFLAGS) $^ $(CXXLIBS) -o $@.o

clean:
	rm -f *.o all