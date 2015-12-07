CC=gcc
CFLAGS=-c -Wall
MATHLIB=-lm
DEBUG=-g
SOURCES=stack.c hash.c reverse-polish.c shunting-yard.c calc.c error.c
OBJECTS=$(SOURCES: .c=.o)
EXEC=calc

all:	$(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(MATHLIB) -o $@ $(DEBUG)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o calc
