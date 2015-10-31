CC=gcc
CFLAGS=-c -Wall
DEBUG=-g
SOURCES=stack.c reverse-polish.c shunting-yard.c calc.c
OBJECTS=$(SOURCES: .c=.o)
EXEC=calc

all:	$(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(DEBUG)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o calc
