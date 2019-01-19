#!/usr/bin/ruby
require "./utils"

exit 1 if ARGV.length != 1
input = ARGV[0]

puts single_key_xor input
