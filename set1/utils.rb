#!/usr/bin/ruby

def base64_to_decimal(a)
	`echo "#{a}" | ./base64_to_ascii | ./ascii_to_hex | ./hex_to_decimal`
end

def find_key_length(a)
	`echo "#{a}" | ./find_repeating-key_xor_length`.to_i
end

def get_english_score_decimal(a)
	return 0 if a.nil?
	`echo "#{a}" | ./get_english_score_decimal`.to_f
end

def get_english_score(a)
	get_english_score_decimal to_spaced_decimal a 
end

def to_spaced_decimal(a)
	a.split('').collect(&:ord).reduce{|i, j|"#{i} #{j}"}
end

def dec_to_hex_str(a)
	a.collect{|i|"%02x"%i}.join
end

def to_hex(c)
	`echo '#{c}' | ./ascii_to_hex`.chomp(' ')
end

def fixed_xor(a, b)
	`./fixed_xor "#{a}" "#{b}"`.chomp
end

def hex_to_ascii(a)
	`echo '#{a}' | ./hex_to_ascii`.chomp
end

def ascii_to_decimal_arr(a)
        a.split('').map{|i|i.ord}
end

def repeating_key_xor(str, key)
        key = key * (str.size/key.size + 1)
        res = Array.new
        (0..str.size-1).each do |i|
                res << (str[i].to_i ^ key[i].to_i)
        end
        dec_to_hex_str(res)
end

def single_key_xor input
	maxfreq_hex = input.scan(/.{2}/).max_by{ |i| input.scan(/.{2}/).count(i) }
	solutions = []
	my_guesses = "EeTtAaOoIiNn SsHhRrDdLlUu"
	my_guesses.split('').each do |guess|
		culprit_hex = fixed_xor maxfreq_hex, to_hex(guess)
		decoded_hex = fixed_xor input, culprit_hex*(input.length/2)
		decoded_txt = hex_to_ascii decoded_hex
		solutions << {
			score:	get_english_score(decoded_txt),
			text:	decoded_txt,
			hex:	culprit_hex
		}
	end
	solutions.sort{|a, b| b[:score] <=> a[:score]}[0]
end
