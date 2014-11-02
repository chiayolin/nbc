#!/bin/bash
# This file is part of: dtob (Version 1.0)
# Author: Chiayo Lin
# Dare  : Nov. 02, 2014

cd ./src/
make

echo "mv dtob /usr/local/bin"
mv dtob /usr/local/bin
echo "dtob successfully installed :-)"
cd ..
exit 0
