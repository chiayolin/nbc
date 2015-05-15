Number Base Converter
=====================

[![Build Status](https://travis-ci.org/chiayolin/nbc.svg?branch=master)](https://travis-ci.org/chiayolin/nbc)

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


| Options     | Descriptions                                                   |
| ----------- |----------------------------------------------------------------|
| `-h`        | print program's information, such as license, author, and etc. |
| `-f`        | force program enther the interactive mode.                     |
| `-i <base>` | set input number base, \<base\> is required.                   |
| `-o <base>` | set output number base, \<base\> is required.                  |
| `<value>`   | input number value, this value can  not be empty.              |

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

Okay, so now if we want to convert a hexadecimal number `bbb6ae` to a decimal number, then you will need to enter
`nbc -i hex -o dec bbb6ae` into the termianl. However, like what it says above, every number base has three
different forms. Therefore you can either use `nbc -i h -o d bbb6ae`, `nbc -i hexadecimal -o decimal bbb6ae`, or
any liget forms have shown above. This is what it might looks like on the terminal:

`$ nbc -i hex -o dec bbb6ad`

Output:

`12301997`

A shortcut to do it:

`$ nbc -i h -o d bbb6ad`

Output looks the same:

`12301997`

Well, there is a long way to do it as well:

`nbc -i hexadecimal -o decimal bbb6ae`

You will get the same right output:

`12301998`

###Interactive Mode

The program provides a powerful interactive mode, which makes the number base conversion much easier. You can either
enter by just runing the command `nbc`, or with the `-i` argument, `nbc -i`. 

When you get into the interactive mode, you will see a prompt like this:

```
type `help` for help
>
````

You can use the command `help` for help.

```
type `help` for help
> help (Press RETURN)
```

Then you will get a list of available commands. However, every command is defined internally. Use `help COMMAND` to 
find out more about the function `COMMAND`. For example, I want to know more about the command `set`, then I will 
type:

```
> help set (Press RETURN)
```

Output:

```
set - set input/output base.
usage: set [options [values]]
options:
   -i, input   <base>
   -o, output  <base>
values:
   bin, oct, dec, hex
```

Now you get the idea, try every command with `help` if you want.

Okay, so now let's talk about the main function of `nbc`, convert number bases. Let's say you want to convert a 
hexdecimal number `bea` to binary. Then you would want use the `set` command to set input base to hexadecimal, and 
output base to binary. Here is one way to do it:

```
> set input hex (Press RETURN)
> set output bin (Press RETURN)
```

And of course, you can replace `input` with `-i` and `output` with `-o`:

```
> set -i hex (Press RETURN)
> set -o bin (Press RETURN)
```

> Available number bases can be found on the above section. You can always use the `help` command to get more
> information about every command. 

Now you are all set, so just simply enter:

```
> bea
```

Output:

```
101111101010
```

Done!!! :tada:

License
-------

Copyright (C) 2014  Chiayo Lin <chiayo.lin@gmail.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
details.
You should have received a copy of the GNU General Public License along with this program. If not, see 
<http://www.gnu.org/licenses/>.
