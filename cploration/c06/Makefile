CC = gcc
CFLAGS = -Wall -g

all: main

main: main.o parser.o
	$(CC) $(CFLAGS) -o main main.o parser.o

main.o: main.c parser.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

clean:
	del /f *.o main.exe
