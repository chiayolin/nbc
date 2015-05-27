# This file is part of: nbc (Version 0.1-(x))
# Author: Chiayo Lin
# Date  : Dec. 24, 2014

PRG= nbc
COM= gcc
SRC= main.c inte/inte.c core/core.c

$(PRG): $(SRC)
	$(COM) -o $(PRG) $(SRC) -lm

debug:
	$(COM) -Wall -Wextra -g -ggdb -o $(PRG) $(SRC) -lm

install:
	cp $(PRG) /usr/local/bin/

clean:
	$(RM) *.o || true
	$(RM) inte/*.o || true
	$(RM) core/*.o || true
	$(RM) $(PRG) || true
