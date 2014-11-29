#### Under Construction, so do not believe anything you see !

### Number Base Converter

The program, `nbc` is stands for the Number Base Converter. `nbc` is an open source multi-platforms number base converter that written in C. You can use `nbc` to convert between binary, octal, decimal, and hexadecimal number. The program itself also provides a powerful interactive mode, and command line options.

## Installing

### Linux and Mac OS X
1. Open your terminal
2. `git clone http://github.com/chiayolin/dtob`
3. `cd /path/to/dtob`
4. `chmod +x install`
5. `./install`

### Windows
1. Install Linux :-)
2. `git clone http://github.com/chiayolin/dtob`
3. `cd /path/to/dtob`
4. `chmod +x install`
5. `./install`

## Usage

### Command Line
`dtob [-options] [value (binary/decimal) <optional>]`

Here is a list of available options: `-h` `-d` `-b` `-i` `-m`

`-h` : print the help message.

`-d` : convert decimal number to binary.

`-b` : convert binary number to decimal.

`-i` : force interactive mode.

`-m` : print some info about this program.

Arguments `-d` and `-b` expect a number value after. For example, if we want to convert a decimal number 256 to binary, then we will use the argument `-d` with a decimal number 410:

`dtob -d 410`

Output:

`110011010`

Same way for the argument `-b`, which converts binary number to decimal:

`dtob -b 10011001110`

Output:

`1230`

### Interactive Mode

You can either enter interactive mode by just runing the command `dtob`, or with the `-i` argument like, `dtob -i`.

When you get into interactive mode, you will see a prompt like this:

`use h for help` 

`>>> _`

Now you can enter a single character `h` for help. However, here are available options: `h`, `d`, `b`, `m`, and `q`

You can convert a decimal number to binary by using the option `d`. Here is an example:

`machine:~ chiayo$ dtob`

`use h for help` 

`>>> d` (Press RETURN)

`1112 ` (Press RETURN)

`10001011000`

Or from binary to decimal number:

`...`

`>>> b` (Press RETURN)

`1100101010` (Press RETURN)

`810`

When you whant to exit the interactive mode, just simply type `q` then hit return:

`>>> q` (Press RETURN)

## License

Copyright (C) 2014  Chiayo Lin <chiayo.lin@gmail.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
