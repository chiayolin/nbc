/*
 * nbc - shell.c - interactive mode
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
#include "./__inte.h"
#include "./inte.h"

/* Store input/output settings as external variables */
int InNumBase, OutNumBase;

/* Scan an array, return index if there is a token */
int scan(const char *array, const char *tokens[]) {
	int index = 0;
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

/* Interactive mode */
void interactive() {
	int argc, i, size;
	extern int InNumBase, OutNumBase;
	char input[MAX], output[MAX], *arg[MAX];

	const char *token[] = {
		"set", "help", "info", "quit", "state", "swap" };
	enum { 
		SET = 0, HELP, INFO, QUIT, STATE, SWAP }; /* Numberic value for tokens */

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

		i = scan(arg[0], token);

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
				size = convert(InNumBase, OutNumBase, arg[0], output);
				printa(output, size);
			break;	
		}
	}
}

/* Function: SET */
void c_set(char *arg[], const int argc, const char *tokens[]) { 
	extern int InNumBase, OutNumBase;
	int type, buff;

	const char *token[] = {
		"input", "-i", "output", "-o", "bin", "oct", "dec", "hex" };
	enum { 
		INPUT, I, OUTPUT, O, C_BIN, C_OCT, C_DEC, C_HEX }; /* Numberic value for tokens */


	if(argc >= 4)
		printf("error: too many arguments.\n");
	else if(argc != 3)
		printf("error: too few arguments.\n");
	else {
		/* Step 1. Read variable */
		int i;
		i = scan(arg[1], token);
		switch(i) {
		case INPUT: case I:
			type = INPUT;
			break;
		case OUTPUT: case O:
			type = OUTPUT;
			break;
		default:
			printf("error: '%s' is not a variable.\n", arg[1]);
			break;
		}

		/* Step 2. Read number base */
		i = scan(arg[2], token);
		switch(i) {
		case C_BIN:
			buff = BIN;
			break;
		case C_OCT:
			buff = OCT;
			break;
		case C_DEC:
			buff = DEC;
			break;
		case C_HEX:
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
			puts("BIN");
			break;
		case OCT:
			puts("OCT");
			break;
		case DEC:
			puts("DEC");
			break;
		case HEX:
			puts("HEX");
			break;
		default:
			puts("ERR");
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
		puts("use dtob -h for help");
		break;
	case 1:
		puts("usage: dtob [options] [value ...]");
		printf("  -h      %s", h);
		printf("  -d      %s", d);
		printf("  -b      %s", b);
		printf("  -i      %s", i);
		printf("  -m      %s", m);
		break;

	case 2:
		puts("list of commands:");
		puts("  help    print this help message.");
		puts("  set     set input/ouput base.");
		puts("  state   display input/output setting.");
		puts("  swap    swap input/output base.");
		puts("  info    print the information.");
		puts("  quit    quit the program.");
		break;
	}
}

/* Print some information about this program */
void c_info() {
	printf("nbc version, %s\n", VERSION);
	printf("complied on, %s %s\n\n", __TIME__, __DATE__);
	puts("Number Base Converter (c) 2014 chiayolin.org");
	puts("Source Code: <http://github.com/chiayolin/nbc/>");
	puts("Author     : Chiayo Lin <chiayo.lin@gmail.com>");
	puts("License    : GPL 3.0");
}
