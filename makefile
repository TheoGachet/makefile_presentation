CC=gcc
CFLAGS= -I./include
LDFLAGS=

SRCDIR=./src
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)

EXECUTABLE=test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) main.o
	$(CC) $(LDFLAGS) $(OBJECTS) main.o -o $@ -lm

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -lm 

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@ -lm

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

	