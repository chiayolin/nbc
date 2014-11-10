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

#define MAX 1000 /* Maximum arrray size */

/* Number Bases Conversions */
int btod(int binary[MAX], const int size); 	/* Convert Bin. to Dec. */
int dtob(int decimal, int binary[MAX]); 	/* Convert Dec. to Bin. */


int getaton(int array[MAX]); /* Read ASCII numbers into an array, convert to numbers, return size */
void printa(const int array[MAX], const int size); /* Print an array */
void reverse(int array[MAX], const int size); /* Reverse an array */
void interactive(); /* Interactive mode */
void help(int type); /* Print help messages base on the varible 'type' */
void info(); /* Print some information about this program */

#endif
