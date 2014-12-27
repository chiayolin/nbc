#### Under Construction, Do Not Believe Anything You See !

Number Base Converter
=====================

The program, `nbc` is stands for the Number Base Converter. `nbc` is an open source multi-platforms number base
converter written in C. You can use `nbc` to convert between binary, octal, decimal, and hexadecimal number. The
program itself also provides a powerful interactive mode, as well as command line options.

Installing
----------

### Linux and Mac OS X
1. Open your terminal
2. `git clone http://github.com/chiayolin/nbc`
3. `cd /path/to/nbc`
4. `chmod +x install`
5. `./install`

### Windows
1. Install Linux :-)
2. `git clone http://github.com/chiayolin/nbc`
3. `cd /path/to/nbc`
4. `chmod +x install`
5. `./install`

Usage
-----

###Command Line
`nbc [ -h | -m | -f ] [ -i <in base>] [ -o <out base>] [ <value> ]`

Here is a list of available options: `-h` `-m` `-f` `-i` `-o`

| options     | descriptions            |
| ----------- |-------------------------|
| `-h`        | print more prog's info  |
| `-f`        | force interactive mode  |
| `-i <base>` | set input number base   |
| `-o <base>` | set output number base  |
| `value`     | input number value      |

Here are four different in/out bases, and each base has three different form.

`b`, `bin`, `binary`

`o`, `oct`, `octal`

`d`, `dec`, `decimal`

`h`, `hex`, `hexadecimal`

Arguments `-i` and `-o` expect a number base after, and both arguments need to be used at the same time. However, 
the `<value>` can not be empty. For example, when you want to convert a decimal number `332000` to a binary 
number, all you need is enter: `nbc -i dec -o bin 332000` into the termianl.

`$ nbc -i dec -o bin 332000`

Output:

`1010001000011100000`

Okay, so now if we want ot convert a hexadecimal number `bbb6ae` to a decimal number, then you will need yo enter
`nbc -i hex -o dec bbb6ae` into the termianl. Else just like what it says above, every number base has three
different forms. Therefore you can either enter `nbc -i h -o d bbb6ae`, `nbc -i hexadecimal -o decimal bbb6ae`, or
any liget forms have shown above. This is what it might looks like on terminal:

`$ nbc -i hex -o dec bbb6ae`

Output:

`12301998`

###Interactive Mode

License
-------

Copyright (C) 2014  Chiayo Lin <chiayo.lin@gmail.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see 
<http://www.gnu.org/licenses/>.
