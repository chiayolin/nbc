/*
 * nbc - core.c
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

#include "core.h"
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/* Store input/output settings as external variables */
int InNumBase, OutNumBase;

/* Conversion interface */
void convert(const int from, const int to, char *input) {
	int com, size; 
	com = size = 0;
	size = strlen(input);

	switch(from) {
		case BIN:
			com = btod(input, size);
			break;
		case OCT:
			com = otod(input, size);
			break;
		case DEC:
			com = atoi(input);
			break;
		case HEX:
			com = htod(input, size);
			break;
	}

	switch(to) {
		case BIN:
			size = dtob(com, input);
			break;
		case OCT:
			size = dtoo(com, input);
			break;
		case DEC:
			printf("%d\n", com);
			return;
			break;
		case HEX:
			size = dtoh(com, input);
			break;
	}

	printa(input, size);
	
	return;
}

/* Convert Dec. to Bin */
int dtob(int decimal, char *binary) {
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

/* Convert Dec. to Oct. */
int dtoo(int decimal, char *octal) {
	int i, size;
	if(decimal == 0) {
		octal[0] = 0;
		return 1;
	} /* octal[0] = 0 when decimal is 0 */

	for(i = 0, size = 0; decimal != 0; i++, size++) {
		octal[i] = (decimal % 8) + '0';
		decimal = decimal / 8;
	}
	reverse(octal, size);
	
	return size;
}

/* Convert Dec. to Hex. */
int dtoh(int decimal, char *hexadecimal) {
	int i, size;
	if(decimal == 0) {
		hexadecimal[0] = '0';
		return 1;
	}

	for(i = 0, size = 0; decimal != 0; i++, size++) {
		hexadecimal[i] = (decimal % 16) + '0';
		if((hexadecimal[i] - '0') > 9)
			hexadecimal[i] += 39;
		decimal = decimal / 16;
	}
	reverse(hexadecimal, size);

	return size;
}

/* Convert Bin. to Dec. */
int btod(char *binary, const int size) {
	int i, decimal;
	i = decimal = 0;

	reverse(binary, size);
	for(i = 0; i < size; i++)
		decimal = decimal + ((binary[i] - '0') * (pow(2, i)));

	return decimal;
}

/* Convert Oct. to Dec. */
int otod(char *octal, const int size) {
	int i, decimal;
	i = decimal = 0;
	
	reverse(octal, size);
	for(i = 0; i < size; i++)
		decimal = decimal + ((octal[i] - '0') * (pow(8, i)));
	
	return decimal;
}

/* Convert Hex. to Dec. */
int htod(char *hexadecimal, const int size) {
	int i, decimal, type;
	i = decimal = type = 0;

	/* x = from char to int, y = from char(letter) to int */
	int type_x = '0', type_y = 'W';
	
	reverse(hexadecimal, size);
	for(i = 0; i < size; i++) {
		(!isdigit(hexadecimal[i])) ? (type = type_y) : (type = type_x);
		decimal = decimal + ((hexadecimal[i] - type) * (pow(16, i)));
	}

	return decimal;
}

/* Scan an array, return index if there is a token */
int scan(const char *array, const char *tokens[], int index) {
	while(strcmp(array, tokens[index]) != 0)
		++index;

	return index;
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
void printa(const char *array, const int size) {
	int i;
	for(i = 0; i < size; i++)
		printf("%c", array[i]);
	printf("\n");
}

/* Reverse an array */
void reverse(char *array, const int size) {
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
	int argc, i;
	extern int InNumBase, OutNumBase;
	char input[MAX], *arg[MAX];
	const char *token[] = {
		"set", "help", "info", "quit", "state", "swap",
		"input", "output", "bin", "oct", "dec", "hex" };

	InNumBase = OutNumBase = DEC;
	argc = i = 0;

	printf("type help for help\n");
	while(1) {
		printf(KCYN ">>> " RESET);
		read(input);
		if(input[0] == '\0')
			continue; /* Continue if user did't enter nothing */

		argc = 0;
		for(i = 0, arg[i] = strtok(input, " "); 
			arg[i] != NULL; arg[i] = strtok(NULL, " "))
				++i, ++argc;

		i = 0;
		i = scan(arg[0], token, i);

		switch(i) {
			case SET:
				c_set(arg, argc, token);
				break;
			case HELP:
				c_help(2);
				break;
			case INFO:
				c_info();
				break;
			case STATE:
				c_state();
				break;
			case SWAP:
				c_swap();
				break;
			case QUIT:
				return;
				break;
			default:
				if(argc != 1)
					printf("error: `%s` command not found\n", arg[0]);
				else 
					convert(InNumBase, OutNumBase, arg[0]);
				break;
		}
	}
}

/* Function: SET */
void c_set(char *arg[], const int argc, const char *tokens[]) { 
	extern int InNumBase, OutNumBase;
	int type, buff;

	if(argc >= 4)
		printf("error: too many arguments.\n");
	else if(argc != 3)
		printf("error: too few arguments.\n");
	else {
		/* Step 1. Read variable */
		int i = 6;
		i = scan(arg[1], tokens, i);
		switch(i) {
			case INPUT:
				type = INPUT;
				break;
			case OUTPUT:
				type = OUTPUT;
				break;
			default:
				printf("error: '%s' is not a variable.\n", arg[1]);
				break;
		}

		/* Step 2. Read number base */
		i = 8;
		i = scan(arg[2], tokens, i);
		switch(i) {
			case BIN:
				buff = BIN;
				break;
			case OCT:
				buff = OCT;
				break;
			case DEC:
				buff = DEC;
				break;
			case HEX:
				buff = HEX;
				break;
			default:
				printf("error: '%s' is not a number base.\n", arg[2]);
				return; /* Skip Step 3. if buff is not a number base */
				break;
		}

		/* Step 3. Store result into the external variable */
		switch(type) {
			case INPUT:
				InNumBase = buff;
				break;
			case OUTPUT:
				OutNumBase = buff;
				break;
			default:
				break;
		}

		return;
	}

}

/* Display user's input/output settings */
void c_state() {
	int buff, i;
	for(i = 0; i <= 1; ++i) {
		if(i == 0) {
			printf("input : ");
			buff = InNumBase;
		}
		else {
			printf("output: ");
			buff = OutNumBase;
		}

		switch(buff) {
			case BIN:
				printf("BIN\n");
				break;
			case OCT:
				printf("OCT\n");
				break;
			case DEC:
				printf("DEC\n");
				break;
			case HEX:
				printf("HEX\n");
				break;
			default:
				printf("NULL\n");
				break;
		}
	}

	return;
}

void c_swap() {
	extern int InNumBase, OutNumBase;
	int temp;
	temp = OutNumBase;
	OutNumBase = InNumBase;
	InNumBase = temp;

	return;
}

/* Print help messages base on the varible 'type' */
void c_help(int type) {
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
			printf("list of commands:\n");
			printf("  help    print this help message.\n");
			printf("  set     set input/ouput base.\n");
			printf("  state   display input/output setting.\n");
			printf("  swap    swap input/output base.\n");
			printf("  info    print the information.\n");
			printf("  quit    quit the program.\n");
			break;
	}
}

/* Print some information about this program */
void c_info() {
	printf("nbc version, %s\n", VERSION);
	printf("complied on, %s %s\n\n", __TIME__, __DATE__);
	printf("Number Base Converter (c) 2014 chiayolin.org\n");
	printf("Source Code: <http://github.com/chiayolin/dtob/>\n");
	printf("Author     : Chiayo Lin <chiayo.lin@gmail.com>\n");
	printf("License    : GPL 3.0\n");
}
