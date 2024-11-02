CC=g++
CFLAGS=-Wall -O2 -std=c++11 -c
LDFLAGS=-s
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/minusBGradusovCPP

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@if not exist "bin" mkdir bin
	$(CC) obj/$(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	@if not exist "obj" mkdir obj
	$(CC) $(CFLAGS) $< -o obj/$@
