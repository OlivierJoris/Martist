CC=g++
FLAGS=-g -std=c++17 -Wall -Wextra
PROGRAM=martist

SOURCES=main.cpp Martist.cpp Expression.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(PROGRAM)

martist: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm $(PROGRAM)
	clear