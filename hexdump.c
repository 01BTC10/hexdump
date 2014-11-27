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

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void print_cp437(unsigned char buf[], size_t len)
{
	size_t i;
	wchar_t cp[] = L"␀☺☻♥♦♣♠•◘○◙♂♀♪♫☼►◄↕‼¶§▬↨↑↓→←∟↔▲▼ !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~⌂ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜ¢£¥₧ƒáíóúñÑªº¿⌐¬½¼¡«»░▒▓│┤╡╢╖╕╣║╗╝╜╛┐└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤╥╙╘╒╓╫╪┘┌█▄▌▐▀αßΓπΣσµτΦΘΩδ∞φε∩≡±≥≤⌠⌡÷≈°∙·√ⁿ²■␣";

	for (i = 0; i < 16; i++)
		if (i < len)
			putwchar(cp[buf[i]]);
	putwchar('\n');
}

void print_hex_be(unsigned char buf[], size_t len)
{
	size_t i;

	for (i = 0; i < 16; i++) {
		if (i < len)
			wprintf(L"%02X", buf[i]);
		else
			wprintf(L"  ");
		if (i % 2)
			putwchar(' ');
	}
	putwchar(' ');
}

int main(int argc, char *argv[])
{
	size_t len;
	unsigned char buf[16];
	unsigned int addr = 0;
	FILE *fp = NULL;

	setlocale(LC_CTYPE, "");

	if (argc > 1)
		fp = fopen(argv[1], "r");
	/* fp is NULL when there is no arg or when fopen fails */
	if (fp == NULL)
		fp = stdin;
	while ((len = fread(buf, 1, 16, fp)) > 0) {
		wprintf(L"%08X: ", addr);
		print_hex_be(buf, len);
		print_cp437(buf, len);
		if (len < 16)
			wprintf(L"%08X:\n", addr + (unsigned int) len);
		addr += 16;
	}
	fclose(fp);

	return 0;
}
