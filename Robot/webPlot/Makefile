CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=webplot.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=prog


all: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJECTS)
	rm -f gmon.out