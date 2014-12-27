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

#include "./core/core.h"
#include "./inte/inte.h"

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000
#define END "\0"
#define IS_ERR -1
#define IS_END (strcmp(tokens[index], END) == 0)

int InNumBase, OutNumBase;

/* verifies arg, return 0 if is illegal */
int verify_arg(const char *array, const int input_base, const int argc);

/* scan if *optarg* is a token, then return index */
int opt_arg_scan(const char *array, const char *tokens[]);

/* set input/output number base from *[in|out]_base_value */
int set_base(const char *in, const char *out);

/* print help messages and the usage */
void print_help(bool is_err);

int main(const int argc, char *argv[]) {
	if(argc == 1) {
		interactive();
		return 0;
	}

	char *in_base_value = NULL,
	     *out_base_value = NULL;
	int iflag, oflag, index, c;
	
	iflag = oflag = c = 0;
	opterr = 0;
	
	/* read command line options and args */
	while((c = getopt(argc, argv, "i:o:hmf")) != -1) {
		switch(c) {
		case 'h':
			print_help(!IS_ERR);
			return 0;
		case 'm':
			info();
			return 0;
		case 'f':
			interactive();
			return 0;
		case 'i':
			in_base_value = optarg;
			iflag = 1;
			break;
		case 'o':
			out_base_value = optarg;
			oflag = 1;
			break;
		case '?':
			if((optopt == 'i') || (optopt == 'o'))
				fprintf(stderr, "error: option -%c requires an argument.\n", optopt); 
			else if(isprint(optopt)){
				fprintf(stderr, "error: unknown option `-%c'.\n", optopt);
				print_help(IS_ERR);
			}
			else
				fprintf(stderr, "error: unknown option char `\\x%x'.\n", optopt);
			return 1;
		default:
			return 1;
		}
	}
	
	/* exit if either oflag or iflag has not been set */
	if(iflag != 1 || oflag != 1) {
		fprintf(stderr, "error: in/out base must be specific.\n");
		return 0;
	}

	/* set In/OutNumBase base on in/out_base_value */
	extern int InNumBase, OutNumBase;
	int error = set_base(in_base_value, out_base_value);
	if(error == IS_ERR) {
		fprintf(stderr, "error: couldn't set number base.\n");
		return 1;
	}

	if(argc < 6) {	
		fprintf(stderr, "error: no input value!\n");
		return 1;
	}

	char result[MAX];
	for(index = optind; index < argc; index++) {
		if(!verify_arg(argv[index], InNumBase, argc)){
			fprintf(stderr, "error: illegal char(s)\n");
			return 1;
		}
		else {
			convert(InNumBase, OutNumBase, argv[index], result);
			printf("%s\n", result);
		}
	}

	return 0;

}

/* verifies arg, return 0 if is illegal */
int verify_arg(const char *array, const int input_base, const int argc) {
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
		fprintf(stderr, "error: lower case only.\n");
	
	return (illegal != 0 || argc != 6) ? 0 : 1;
}

int opt_arg_scan(const char *array, const char *tokens[]) {	
	if(array == NULL)
		return IS_ERR;
	
	int index = 0;
	while(strcmp(array, tokens[index]) != 0 && !IS_END)
		index++;

	return IS_END ? IS_ERR : index;
}

int set_base(const char *in, const char *out) {
	const char *tokens[] = { 
		"b", "o", "d", "h",
		"bin", "oct", "dec", "hex",
		"binary", "octal", "decimal", "hexadecimal", END};
	enum {
		A_B = 0, A_O, A_D, A_H, A_BIN, A_OCT, A_DEC, A_HEX,
		A_BINARY, A_OCTAL, A_DECIMAL, A_HEXADECIMAL };
	
	if(in == NULL || out == NULL)
		return IS_ERR;
	
	extern int InNumBase, OutNumBase;
	InNumBase = opt_arg_scan(in, tokens);
	OutNumBase = opt_arg_scan(out, tokens);

	int i, buff, error;
	buff = error = 0;

	for(i = 1; i <= 2; i++) {
		if(i != 1)
			buff = OutNumBase;
		else
			buff = InNumBase;

		switch(buff) {
		case A_B: case A_BIN: case A_BINARY:
			buff = BIN;
			break;
		case A_O: case A_OCT: case A_OCTAL:
			buff = OCT;
			break;
		case A_D: case A_DEC: case A_DECIMAL:
			buff = DEC;
			break;
		case A_H: case A_HEX: case A_HEXADECIMAL:
			buff = HEX;
			break;
		default:
			if(i != 1)
				fprintf(stderr, "error: '%s' is not a number base.\n", out);
			else
				fprintf(stderr, "error: '%s' is not a number base.\n", in);
			error = 1;
			break;
		}

		if(i != 1)
			OutNumBase = buff;
		else 
			InNumBase = buff;
	}
	
	return error ? IS_ERR : 0;
}

void print_help(bool is_err) {
	if(is_err)
		puts("use `nbc -h` for help");
	else {
		puts("usage: nbc [-h|-m|-f] [-i <in base>]");
		puts("           [-o <out base>] [<value>]");
		puts("options:");
		puts("  -h         print this help message");
		puts("  -m         print more prog's info");
		puts("  -f         force interactive mode");
		puts("  -i <base>  set input number base");
		puts("  -o <base>  set output number base");
		puts("  <value>    input number value\n");
		puts("in/out base:");
		puts("  b, bin, binary");
		puts("  o, oct, octal");
		puts("  d, dec, decimal");
		puts("  h, hex, hexdecimal\n");
		puts("both -i and -o options need to be used at");
		puts("the same time, and <value> can't be empty");

	}
}
