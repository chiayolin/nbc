![DTOB](https://dl.dropboxusercontent.com/u/221687308/www/resources/github/dtob_logo.png)

DTOB is written in C and it stands for <b>Decimal to Binary and Binary to Decimal Converter</b>. Therefore, you can use DTOB to convert binary numbers to decimal numbers, or decimal numbers to binary numbers. It provides two ways to convert number bases. You can ethier input numbers directly through the terminal, or enter the interactive mode.

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

`-i` : force the program enter interactive mode.

`-m` : print information about this program.

Option `-d` and option `-b` expects a number value after. For example, if we want to convert a decimal number 1112 to binary, then we will use the argument `-d` and a decimal number 1112:

`dtob -d 1112`
