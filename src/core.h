/*
 * dtob - core.h
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

#ifndef CORE_H
#define CORE_H

#define VERSION 1.1 /* Program version */
#define MAX 1000 /* Maximum arrray size */

enum { 
	SET = 0, HELP, INFO, QUIT, STATE, CONVERT, 
	INPUT, OUTPUT, BIN, OCT, DEC, HEX }; /* Numberic value for tokens */

/* Number Bases Conversions */
int btod(char binary[MAX], const int size); 	/* Convert Bin. to Dec. */
int otod(char octal[MAX], const int size);	/* Convert Oct. to Dec. */
int dtob(int decimal, char binary[MAX]); 	/* Convert Dec. to Bin. */
int dtoo(int decimal, char octal[MAX]);		/* Convert Dec. to Oct. */

void printa(const char array[MAX], const int size); /* Print an array */
void reverse(char array[MAX], const int size); /* Reverse an array */

void interactive(); /* Interactive mode */
void read(char *array); /* Read user's input into an array */
int scan(const char *array, const char *tokens[], int index); /* Return index if there's token in array */
void c_set(char *arg[], const int argc, const char *tokens[]); /* Function: SET */
void c_state(); /* Display user's settings */
void c_help(int type); /* Print help messages base on the varible 'type' */
void c_info(); /* Print some information about this program */

#endif
