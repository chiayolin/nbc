#!/bin/bash

cd ./src/
make

echo "mv dtob /usr/local/bin"
mv dtob /usr/local/bin
echo "dtob successfully installed :-)"
cd ..
exit 0
