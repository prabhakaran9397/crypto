#!/bin/bash

for i in `cat 4.txt`; do ./single-byte_XOR_cipher.sh $i; done > guesses_for_4.txt

grep -E "^[a-z A-Z]*$" guesses_for_4.txt | grep '\S' | less

