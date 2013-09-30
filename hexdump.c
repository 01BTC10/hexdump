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

void print_ascii(unsigned char buf[], size_t cnt)
{
	unsigned int i;

	for (i = 0; i < 16; i++) {
		if (i < cnt) {
			if ((buf[i] < 32) || (buf[i] > 126)) {
				putchar('.');
			} else {
				putchar(buf[i]);
			}
		}
	}

	putchar('\n');
}

void print_hex(unsigned char *ptr, size_t cnt)
{
	unsigned int i;

	for (i = 0; i < 16; i++) {
		if (i < cnt) {
			printf("%02X", *ptr++);
		} else {
			printf("  ");
		}

		if (i % 2 == 1) {
			putchar(' ');
		}
	}

	putchar(' ');
}

int main(int argc, const char *argv[])
{
	size_t cnt;
	unsigned int addr = 0;
	unsigned char *ptr, buf[16];
	FILE *fp = NULL;

	if (argc > 1) {
		fp = fopen(argv[1], "r");
	}

	/* fp is NULL when there is no arg or when fopen fails */
	if (fp == NULL) {
		fp = stdin;
	}

	while ((cnt = fread(buf, sizeof(char), 16, fp)) > 0) {
		printf("%08X: ", addr);
		addr += 16;
		ptr = buf;
		print_hex(ptr, cnt);
		print_ascii(buf, cnt);
	}

	/* Do the polite thing */
	fclose(fp);

	return 0;
}
