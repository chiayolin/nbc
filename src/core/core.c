/*
 * nbc - core.c - conversion core implementation.
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

#include "./core.h"
#include "./__core.h"

/* External interface */
int convert(const int from, const int to, char *input, char *output) {
	int size = pos_process(output, 
		pre_process(input, strlen(input), from), to);

	return size; /* Return the size of output[] */
}

/* Generates and return a 64 bit *common* */
uint64_t pre_process(char *input, const int size, const int from) {
	uint64_t common = 0;
	int i, base;
	base = from;

	/* (x= from char to int, y= from char(letter) to int) in Hex. */
	int type, type_x, type_y = 'W';
	type = type_x = '0';

	reverse(input, size);
	for(i = 0; i < size; i++) {
		if(base == HEX)
			(!isdigit(input[i])) ? (type = type_y) : (type = type_x);
		common = common + ((input[i] - type) * (pow(base, i)));
	}

	return common;
}

/* Processes *common* and return the size of output array*/
int pos_process(char *output, uint64_t common, const int to) {
	if(common == 0)
		/* terminate with output = '0' when common is 0 */
		return (output[0] = '0') != '0' ? 0 : 1;

	int i, size, base = to;
	bool ishex = (base != HEX) ? 0 : 1;

	for(i = 0, size = 0; common != 0; i++, size++) {
		output[i] = (common % base) + '0';

		if(ishex && ((output[i] - '0') > 9))
			output[i] += 39; /* Magical mystery number */

		common = common / base;
	}

	reverse(output, size);
	return size; /* Return the size of array */
}

/* Reverse an array */
void reverse(char *array, const int size) {
	char temp[MAX];
	int i, j;

	for(i = 0; i < size; i++)
		temp[i] = array[i]; /* Copy array into a buffer */
	for(i = 0, j = size - 1; j >= 0; i++, j--)
		array[i] = temp[j]; /* Then put it back */
}
