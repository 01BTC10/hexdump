/*
 * hexdump.c
 *
 * Copyright (c) 2013 Boohbah <boohbah at gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

void print_ascii(const unsigned char buf[], const size_t len)
{
	size_t i;

	for (i = 0; i < 16; i++) {
		if (i < len) {
			if ((buf[i] < 32) || (buf[i] > 126)) {
				putchar('.');
			} else {
				putchar(buf[i]);
			}
		}
	}
	putchar('\n');
}

void print_hex_le(const unsigned char buf[], const size_t len)
{
	size_t i;

	for (i = 0; i < 16; i += 2) {
		if (i < len) {
			if (i + 1 < len) {
				printf("%02X", buf[i + 1]);
			} else {
				printf("00");
			}
			printf("%02X ", buf[i]);
		} else {
			printf("     ");
		}
	}
	putchar(' ');
}

void print_hex_be(const unsigned char buf[], const size_t len)
{
	size_t i;

	for (i = 0; i < 16; i++) {
		if (i < len) {
			printf("%02X", buf[i]);
		} else {
			printf("  ");
		}
		if (i % 2) {
			putchar(' ');
		}
	}
	putchar(' ');
}

int main(const int argc, const char *argv[])
{
	size_t len;
	unsigned int addr = 0;
	unsigned char buf[16];
	FILE *fp = NULL;

	if (argc > 1) {
		fp = fopen(argv[1], "r");
	}
	/* fp is NULL when there is no arg or when fopen fails */
	if (fp == NULL) {
		fp = stdin;
	}
	while ((len = fread(buf, sizeof(char), 16, fp)) > 0) {
		printf("%08X: ", addr);
		print_hex_be(buf, len);
		print_ascii(buf, len);
		if (len < 16) {
			printf("%08X:\n", addr + (unsigned int) len);
		}
		addr += 16;
	}
	fclose(fp);
	return 0;
}
