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

/* Store prompt as an external variable */
char Prompt[MAX] = "> ";

/* Scan an array, return index if there is a token */
int scan(const char *array, const char *tokens[]) {
	int index = 0;
	
	while(strcmp(array, tokens[index]) != 0 && !IS_END)
			++index;
	
	return IS_END ? DEFAULT : index;
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

/* verifies user's input, return 0 if is illegal */
int verify(const char *array, const int input_base, const int argc) {
	int i, illegal = 0;
	bool ishex = (input_base != HEX) ? 0 : 1,
	     upper = 0;

	for(i = 0; array[i] != '\0'; i++) {
		if(!islower(array[i]) && isalpha(array[i]))
			++illegal, upper = 1;

		if(ishex && !isxdigit(array[i]))
			++illegal;
		else if(!ishex && ((!isdigit(array[i]))
			|| ((array[i] - '0') >= input_base)))
				++illegal;
	}
	if(upper)
		puts("error: lower case only");

	return (illegal != 0 || argc != 1) ? 0 : 1;
}

/* Interactive mode */
void interactive() {
	int argc, i, size;
	extern int InNumBase, OutNumBase;
	char input[MAX], output[MAX], *arg[MAX];

	const char *token[] = {
		"set", "help", "info", "quit", "state", "swap", "prompt", END };
	enum { 
		SET = 0, HELP, INFO, QUIT, STATE, SWAP, PROMPT }; /* Numberic value for tokens */

	InNumBase = OutNumBase = DEC;
	argc = i = 0;
	
	extern char Prompt[MAX];
	puts("type `help` for help");
	while(1) {
		printf(KCYN "%s" RESET, Prompt);
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
			c_set(arg, argc);
			break;
		case HELP:
			c_help(arg, argc);
			break;
		case INFO:
			info();
			break;
		case STATE:
			c_state();
			break;
		case SWAP:
			c_swap();
			break;
		case PROMPT:
			c_prompt(arg, argc);
			break;
		case QUIT:
			return;
			break;
		default:
			if(!verify(arg[0], InNumBase, argc))
				puts("error: illegal char(s)");
			else {
				size = convert(InNumBase, OutNumBase, arg[0], output);
				printa(output, size);
			}
			break;	
		}
	}
}

/* Function: SET */
void c_set(char *arg[], const int argc) { 
	extern int InNumBase, OutNumBase;
	int type, buff, i;

	const char *token[] = {
		"input", "-i", "output", "-o", 
		"b", "bin", "binary", 
		"o", "oct", "octal",
		"d", "dec", "decimal",
		"h", "hex", "hexadecimal", END };
	enum { 
		INPUT = 0, I, OUTPUT, O, 
		C_B, C_BIN, C_BINARY,
		C_O, C_OCT, C_OCTAL, 
		C_D, C_DEC, C_DECIMAL, 
		C_H, C_HEX, C_HEXADECIMAL }; /* Numberic value for tokens */


	if(argc >= 4)
		printf("error: too many arguments.\n");
	else if(argc != 3)
		printf("error: too few arguments.\n");
	else {
		/* Step 1. Read variable */
		i = 0;
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
		i = 0;
		i = scan(arg[2], token);
		switch(i) {
		case C_B: case C_BIN: case C_BINARY:
			buff = BIN;
			break;
		case C_O: case C_OCT: case C_OCTAL:
			buff = OCT;
			break;
		case C_D: case C_DEC: case C_DECIMAL:
			buff = DEC;
			break;
		case C_H: case C_HEX: case C_HEXADECIMAL:
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

/* Set prompt */
void c_prompt(char *arg[], int argc) {
	extern char Prompt[MAX];
	
	if(argc > MAX - 1)
		puts("error: prompt is too long.");

	else if(argc != 1) {
		if(!strcmp(arg[1], "null")) {
			strcpy(Prompt, "");
			return;
		}

		strcpy(Prompt, arg[1]);
		Prompt[strlen(Prompt)] = ' ';
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
			puts("binary");
			break;
		case OCT:
			puts("octal");
			break;
		case DEC:
			puts("decimal");
			break;
		case HEX:
			puts("hexadecimal");
			break;
		default:
			puts("unknown");
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

/* Print help messages */
void c_help(char *arg[], const int argc) {
	const char *token[] = {
		"help", "set", "state", "swap", "info", "prompt", 
		"quit", END };
	enum {
		HELP = 0, SET, STATE, SWAP, INFO, PROMPT, QUIT };

	int type = (argc != 1) ? scan(arg[1], token) : DEFAULT;

	switch(type) {
	case SET:
		puts("set - set input/output base.");
		puts("usage: set [options [values]]");
		puts("options:");
		puts("   -i, input   <base>");
		puts("   -o, output  <base>");
		puts("values:");
		puts("   b, bin, binary");
		puts("   o, oct, octal");
		puts("   d, dec, decimal");
		puts("   h, hex, hexadecimal");
		break;
	case STATE:
		puts("state - display input/output setting.");
		puts("usage: state");
		break;
	case SWAP:
		puts("swap - swap input/output base.");
		puts("usage: swap");
		break;
	case INFO:
		puts("info - print prog's infomation.");
		puts("usage: info");
		break;
	case PROMPT:
		puts("prompt - set prompt's string.");
		puts("usage: prompt [string|null]");
		puts("prompt will be removed if arg is \"null\".");
		break;
	case QUIT:
		puts("quit - quit the program.");
		puts("usage: quit");
		break;
	case HELP: default:
		puts("usage: help [commands]");
		puts("list of commands:");
		puts("   help    print this help message.");
		puts("   set     set input/ouput base.");
		puts("   state   display input/output setting.");
		puts("   swap    swap input/output base.");
		puts("   info    print prog's information.");
		puts("   prompt  set prompt's string.");
		puts("   quit    quit the program.");
		break;
	}
}

/* Print prog's infomation */
void info() {
	printf("nbc version, %s\n", VERSION);
	printf("complied on, %s %s\n\n", __TIME__, __DATE__);
	puts("Number Base Converter (c) 2014 chiayolin.org");
	puts("Source Code: <http://github.com/chiayolin/nbc/>");
	puts("Author     : Chiayo Lin <chiayo.lin@gmail.com>");
	puts("License    : GPL 3.0");
}
