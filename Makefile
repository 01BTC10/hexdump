CC=gcc
CFLAGS=-O2 -march=native -std=gnu99 -Wextra -Wall -pedantic -g

all: clean hexdump

hexdump:
	$(CC) $(CFLAGS) hexdump.c -o hexdump

clean:
	rm -f hexdump
