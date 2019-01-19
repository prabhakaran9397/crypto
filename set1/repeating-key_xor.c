#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10000

int char_to_int(char c) {
	return c-'0';
}

char int_to_char(int i) {
	return i+'0';
}

int hex_to_integer(char hex_0, char hex_1)
{
	int first_digit	 = hex_0 > '9' ? hex_0-'a'+10 : char_to_int(hex_0);
	int second_digit = hex_1 > '9' ? hex_1-'a'+10 : char_to_int(hex_1);
	int integer = first_digit*16 + second_digit;
	return integer;
}

char* integer_to_hex(int integer)
{
	char* output = malloc(sizeof(char)*2);
	int first_digit  = integer/16;
	int second_digit = integer%16;
	output[0] = first_digit  > 9 ? first_digit+'a'-10  : int_to_char(first_digit);
	output[1] = second_digit > 9 ? second_digit+'a'-10 : int_to_char(second_digit);
	return output;
}

char* repeating_key_xor(char* input1, char* input2)
{
	char* output = malloc(sizeof(char)*SIZE);
	char* local_copy = malloc(sizeof(char)*2);
	int input_length = strlen(input1);
	int i, j, x;

	for(i=strlen(input2), j=0; i<input_length; i++, j++) {
		input2[i] = input2[j];
	}

	for(i=0; i<input_length; i++) {
		x = input1[i] ^ input2[i];
		local_copy = integer_to_hex(x);
		output[2*i]   = local_copy[0];
		output[2*i+1] = local_copy[1];
	}
	return output;
}

int main(int argc, char* argv[])
{
	char* input1 = malloc(sizeof(char)*SIZE);
	char* input2 = malloc(sizeof(char)*SIZE);
	char* output;
	
	if(argc != 3) {
		printf("Usage: %s \"<string>\" \"<key>\"\n", argv[0]);
		return 1;
	}

	strcpy(input1, argv[1]);
	strcpy(input2, argv[2]);

	output = repeating_key_xor(input1, input2);
	printf("%s\n", output);
	
	return 0;
}
