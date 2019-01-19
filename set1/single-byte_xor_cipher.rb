#!/usr/bin/ruby

my_guesses = "EeTtAaOoIiNn SsHhRrDdLlUu"
input = ARGV.length == 1 ? ARGV[0] : "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

def to_hex(c)
	`echo '#{c}' | ./ascii_to_hex`.chomp(' ')
end

def fixed_xor(a, b)
	`./fixed_xor "#{a}" "#{b}"`.chomp
end

def hex_to_ascii(a) 
	`echo '#{a}' | ./hex_to_ascii`.chomp
end

def get_english_score(a)
	`echo '#{a}' | ./hex_to_ascii | ./get_english_score`.chomp.to_f
end

maxfreq_hex = input.scan(/.{2}/).max_by{ |i| input.scan(/.{2}/).count(i) }

solutions = []

my_guesses.split('').each do |guess|
	culprit_hex = fixed_xor maxfreq_hex, to_hex(guess)
	decoded_hex = fixed_xor input, culprit_hex*(input.length/2)
	decoded_txt = hex_to_ascii decoded_hex
	solutions << {
		score:	get_english_score(decoded_hex),
		text:	decoded_txt,
		hex:	culprit_hex
	}
end

puts solutions.sort{|a, b| b[:score] <=> a[:score]}[0]
