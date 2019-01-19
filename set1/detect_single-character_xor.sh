#!/bin/bash

for i in `cat 4.txt`; do ./single-byte_xor_cipher.rb $i; done | sort -n -k2 -t'>' | tail -1
