CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: main.o

main: main.o spi.o
		$(CC) $(CFLAGS) -o main main.o spi.o

main.o: main.c
		$(CC) $(CFLAGS) -c main.c

spi.o: spi.c spi.h
		$(CC) $(CFLAGS) -c spi.c

clean:
		rm -i main.o main spi.o
