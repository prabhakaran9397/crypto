#!/usr/bin/ruby
require "./utils"

exit 1 if ARGV.length != 1
input_file = ARGV[0]

input = base64_to_decimal File.read(input_file)
keysize = find_key_length input
input = input.split
key = String.new

(0..keysize-1).each do |index|
	block = (index..input.size-1).step(keysize).collect{|i|input[i]}
	key += single_key_xor(dec_to_hex_str block)[:hex]
end
input = input.map(&:to_i)
key   = ascii_to_decimal_arr(hex_to_ascii(key))

puts hex_to_ascii repeating_key_xor input, key
