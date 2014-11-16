/*
 * dtob - main.c
 * Binary to Decimal and Decimal to Binary Converter
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
 
#include "core.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(const int argc, char *argv[]) {
	int binary[MAX], decimal;
	int size;
	
	/* Enter interactive mode if there are no command line options */
	if(argc == 1) {
		interactive();
	} 
	
	/* Read the options if argv[0][0] = '-' */
	else if((*++argv)[0] == '-') {
		int decimal, size;
		char opt = *++argv[0], input[MAX];
		switch(opt) {
			case 'd':
				if(argv[1] == NULL)
					printf("agument to '-%s' is missing, expected a decimal number\n", argv[0]);
				else {
					decimal = atoi(argv[1]);
					size = dtob(decimal, input);
					printa(input, size);
				}
				break;

			case 'b':
				if(argv[1] == NULL)
					printf("agument to '-%s' is missing, expected a binary number\n", argv[0]);
				else {
					size = strlen(argv[1]);
					int i;
					for(i = 0; i < size; i++)
						input[i] = argv[1][i]; 
					decimal = btod(input, size);
					printf("%d\n", decimal);
				}
				break;

			case 'h':
				help(1);
				break;

			case 'i':
				interactive();
				break;

			case 'm':
				info();
				break;

			default:
				 printf("dtob: alas, invalid option '-%s' \n", argv[0]);
				 help(0);
				 break;
		}
	}
	
	/* Else, print the error message */
	else {
		printf("dtob: alas, syntax error :-(\n");
		help(0);
		return 1;
	}
			
	return 0;
}	
