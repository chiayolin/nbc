/*
 * nbc - main.c
 * Number Base Converter
 * Copyright (C) 2014  Chiayo Lin <chiayo.lin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../core/core.h"
#include "./inte.h"

int main(const int argc, char *argv[]) {
	int binary[MAX], decimal;
	int size;

	if(argc == 1)
		interactive();

	/* Read the options if argv[0][0] = '-' */
	else if((*++argv)[0] == '-') {
		int i, size;
		char opt = *++argv[0], input[MAX], output[MAX];
		switch(opt) {
			case 'i':
				if(argv[1] == NULL)
					printf("agument to '-%s' is missing, expected a number\n", argv[0]);
				else {
					size = convert(HEX, DEC, argv[1], output);
					for(i = 0; i < size; i++)
						printf("%c", output[i]);
					puts("");
				}
				break;
			default:
				 printf("nbc: alas, invalid option '-%s' \n use -d\n", argv[0]);
				 break;
		}
	}
	
	/* Else, print the error message */
	else {
		printf("nbc: alas, syntax error :-(\n");
		return 1;
	}
			
	return 0;
}	
