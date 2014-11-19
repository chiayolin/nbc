/*
 * dtob - core.c
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

/* Convert Dec. to Bin */
int dtob(int decimal, char binary[MAX]) {
	int i, size;
	if(decimal == 0) {
		binary[0] = '0';
		return 1;
	} /* binary[0] = 0 when decimal is 0 */

	for(i = 0, size = 0; decimal != 0; i++, size++) {
		binary[i] = (decimal % 2) + '0';
		decimal = decimal / 2;
	}
	reverse(binary, size);

	return size; /* Return the size of array */
}

/* Convert Bin. to Dec. */
int btod(char binary[MAX], const int size) {
	int i, decimal;
	i = decimal = 0;

	reverse(binary, size);
	for(i = 0; i < size; i++)
		decimal = decimal + ((binary[i] - '0') * (pow(2, i)));

	return decimal;
}

/* Read user's input into an array */ 
void read(char *array) {
	int i, c;
	i = c = 0;

	while((c = getchar()) != '\n') {
		array[i] = c;
		++i;
	}
	array[i] = '\0';
}

/* Print an array */
void printa(const char array[MAX], const int size) {
	int i;
	for(i = 0; i < size; i++)
		printf("%c", array[i]);
	printf("\n");
}

/* Reverse an array */
void reverse(char array[MAX], const int size) {
	char temp[MAX];
	int i;
	for(i = 0; i < size; i++)
		temp[i] = array[i]; /* Copy array into a buffer */
	int j;
	for(i = 0, j = size - 1; j >= 0; i++, j--)
		array[i] = temp[j];
}

/* Interactive mode */
void interactive() {
	int argc, i, in, out;
	char input[MAX], *arg[MAX];
	char *token[] = {
		"set", "help", "info", "quit", "state", "convert",
		"input", "output", "bin", "oct", "dec", "hex" };
	enum { 
		SET = 0, HELP, INFO, QUIT, STATE, CONVERT, 
		INPUT, OUTPUT, BIN, OCT, DEC, HEX };

	printf("use h for help\n");
	while(1) {
		printf(">>> ");
		read(input);
		
		argc = 0;
		for(i = 0, arg[i] = strtok(input, " "); 
			arg[i] != NULL; arg[i] = strtok(NULL, " "))
				++i, ++argc;

		
		i = 0;
		while(strcmp(arg[0], token[i]) != 0)
			++i;

		switch(i) {
			case SET: {
				if(argc < 3) printf("missing arugument(s)\n");

				else if(argc == 3) {
					i = 6;
					while(strcmp(arg[1], token[i]) != 0)
						++i;

					switch(i) {
						case INPUT: {
							while(strcmp(arg[2], token[i]) != 0)
								++i;
							switch(i) {
								case BIN:
									in = BIN;
									break;
								case OCT:
									in = OCT;
									break;
								case DEC:
									in = DEC;
									break;
								case HEX:
									in = HEX;
									break;
								default:
									printf("number base not found\n");
									break;
							}
							break;
						}
						case OUTPUT: {
							 while(strcmp(arg[2], token[i]) != 0)
								 ++i;
							 switch(i) {
								case BIN:
									 out = BIN;
									 break;
								case OCT:
									 out = OCT;
									 break;
								case DEC:
									 out = DEC;
									 break;
								case HEX:
									 out = HEX;
									 break;
								default:
									 printf("number base not found\n");
									 break;
							}
							break; 
						}
						default:
							printf("syntax error :-(\n");
							break;
					}	
				}
				break;
			}
			case HELP:
				help(2);
				break;
			case INFO:
				info();
				break;
			case STATE:
				printf("This is state\n");
				break;
			case CONVERT:
				if(argc < 2) printf("expect a value\n");
				else printf("value = %s\n", arg[1]);
				break;
			case QUIT:
				return;
				break;
			default:
				printf("%s: command not found\n", arg[0]);
				break;
		}
	}
}

/* Print help messages base on the varible 'type' */
void help(int type) {
	const char h[] = "print this usage and text\n",
	    	   d[] = "convert decimal to binary\n",
	    	   b[] = "convert binary to decimal\n",
	    	   i[] = "force enter interactive mode\n",
	    	   m[] = "more info about this program\n";

	switch(type) {
		case 0:
			printf("use dtob -h for help\n");
			break;
		case 1:
			printf("usage: dtob [options] [value ...]\n");
			printf("  -h      %s", h);
			printf("  -d      %s", d);
			printf("  -b      %s", b);
			printf("  -i      %s", i);
			printf("  -m      %s", m);
			break;

		case 2:
			printf("list of options:\n");
			printf("  h    %s", h);
			printf("  d    %s", d);
			printf("  b    %s", b);
			printf("  m    %s", m);
			printf("  q    quit\n");
			break;
	}
}

/* Print some information about this program */
void info() {
	printf("dtob (Version %.1f) Copyrights (C) 2014 Chiayo Lin\n", VERSION);
	printf("Binary to Decimal and Decimal to Binary Converter\n\n");
	printf("Source Code: <http://github.com/chiayolin/dtob/>\n");
	printf("Author     : Chiayo Lin <chiayo.lin@gmail.com>\n\n");
	printf("License:\n");
	printf("  This program comes with ABSOLUTELY NO WARRANTY.\n");
	printf("  This is free software, and you are welcome to \n");
	printf("  redistribute it under the terms of GPL v3.0.\n");
	printf("  <http://www.gnu.org/licenses/>\n\n");
}
