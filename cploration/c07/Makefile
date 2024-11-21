CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -mconsole

all: main

main: main.o parser.o symtable.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o main main.o parser.o symtable.o

main.o: main.c parser.h symtable.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h symtable.h
	$(CC) $(CFLAGS) -c parser.c

symtable.o: symtable.c symtable.h
	$(CC) $(CFLAGS) -c symtable.c

clean:
	del /f *.o main.exe
