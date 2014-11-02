![DTOB](https://dl.dropboxusercontent.com/u/221687308/www/resources/github/dtob_logo.png)

DTOB is written in C and it stands for <b>Decimal to Binary and Binary to Decimal Converter</b>. Therefore, you can use DTOB to convert binary numbers to decimal numbers, or decimal numbers to binary numbers. It provides two ways to convert number bases. You can either input numbers directly through the terminal, or enter the interactive mode.

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
`dtob [-options] [value (binary/decimal)(optional)]`

Here is a list of available options: `-h` `-d` `-b` `-i` `-m`

`-h` : prints the help message.

`-d` : convert decimal number to binary.

`-b` : convert binary number to decimal.

`-i` : force interactive mode.

`-m` : print information about this program.

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

`>>> d` -> Press RETURN

`1112 ` -> Press RETURN 

`10001011000`
