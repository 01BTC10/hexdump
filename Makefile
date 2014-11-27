CC=gcc
CFLAGS=-O2 -march=native -Wextra -Wall -pedantic -std=gnu99

all: clean hexdump

asm:
	$(CC) -S hexdump.c
hexdump:
	$(CC) $(CFLAGS) hexdump.c -o hexdump

clean:
	rm -f hexdump hexdump.s
