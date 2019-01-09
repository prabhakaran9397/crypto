#!/bin/bash

xored=1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
guess="EeTtAaOoIiNn SsHhRrDdLlUu"

hexes=`./ascii_to_hex "$guess" | sed 's/../& /g' | tr ' ' '\n' | grep '\S'`
len=`printf $xored | wc -c`
max_occuring=`echo $xored | sed 's/../& /g' | tr ' ' '\n' | grep '\S' | sort | uniq -c | sort -r | cut -d' ' -f8 | head -1`

for i in ${hexes[@]}
do
	single=
	to_be_xored_with=`./fixed_xor $max_occuring $i`
	for j in `seq 1 $((len/2))`
	do
		single=$single$to_be_xored_with
	done
	./fixed_xor $xored $single | ./hex_to_ascii
	echo --------------------------------------
done
