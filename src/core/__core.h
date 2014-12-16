/*
 * nbc - core.h
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

#ifndef __CORE_H
#define __CORE_H

#define MAX 1024

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* Number Base Conversions */
int pre_process(char *input, const int size, const int from); /* Generates *common* */
int pos_process(char *output, int common, const int to); /* Processes *common* */
void reverse(char *array, const int size); /* Reverse an array */

#endif