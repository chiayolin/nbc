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

// #include "./core/core.h"
#include "./inte/inte.h"

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX 1000
#define END "\0"
#define IS_ERR -1
#define IS_END (strcmp(tokens[index], END) == 0)

/* scan if *optarg* is a token, then return index */
int opt_arg_scan(const char *array, const char *tokens[]);

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
	
	while((c = getopt(argc, argv, "i:o:hm")) != -1) {
		switch(c) {
		case 'h':
			puts("this is help");
			break;
		case 'm':
			puts("this is info");
			break;
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
				fprintf(stderr, "option -%c requires an argument.\n", optopt); 
			else if(isprint(optopt))
				fprintf(stderr, "unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			return 1;
		}
	}
	
	printf("iflag= %d, oflag= %d\n", iflag, oflag);
	printf("in_base_value= %s\n", in_base_value);
	printf("out_base_value= %s\n", out_base_value);

	for(index = optind; index < argc; index++)
		printf("value= %s\n", argv[index]);

	return 0;

}

int opt_arg_scan(const char *array, const char *tokens[]) {	
	if(array == NULL)
		return IS_ERR;
	
	int index = 0;
	while(strcmp(array, tokens[index]) != 0 && !IS_END)
		index++;

	return IS_END ? IS_ERR : index;
}
