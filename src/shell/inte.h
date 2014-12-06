/*
 * nbc - inte.h - interactive mode
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

#ifndef INTE_H
#define INTE_H

#define VERSION "2.0(x)-nbc_develop" /* Program version */

/* Define colors */
#define KNRM  "\x1B[0m"	 /* Normal */
#define KRED  "\x1B[31m" /* Red */
#define KGRN  "\x1B[32m" /* Green*/
#define KYEL  "\x1B[33m" /* Yellow */
#define KBLU  "\x1B[34m" /* Blue */
#define KMAG  "\x1B[35m" /* Magenta */
#define KCYN  "\x1B[96m" /* Cyan */
#define KWHT  "\x1B[37m" /* White */
#define RESET "\033[0m"  /* Reset */

int scan(const char *array, const char *tokens[]); /* Return index if there's token in array */
void read(char *array); /* Read user's input into an array */
void printa(const char *array, const int size); /* Print an array */
void c_set(char *arg[], const int argc, const char *tokens[]); /* Function: SET */
void c_swap(); /* Swap user's setting */
void c_state(); /* Display user's settings */
void c_help(int type); /* Print help messages base on the varible 'type' */
void c_info(); /* Print some information about this program */

/* External Interface */
void interactive(); /* Interactive mode */

#endif