CC = gcc
CFLAGS = -Wall -I.

TARGET = main

all: $(TARGET)

$(TARGET): main.c parser.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c parser.c

clean:
	rm -f $(TARGET) *~
