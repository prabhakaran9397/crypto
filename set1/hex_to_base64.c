#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE		1000
#define base64_table	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define pad		'='

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

char* integer_to_binary(int integer)
{
	char* binary = malloc(sizeof(char)*8);
	strcpy(binary, "00000000");
	int i = 7;
	while(integer) {
		binary[i--] = int_to_char(integer%2);
		integer /= 2;
	}
	return binary;
}

int binary_to_integer(char* binary)
{
	int integer = 0;
	int i = 0;
	while(i < 8) {
		integer += char_to_int(binary[i]) << (7-i++);
	}
	return integer;
}

char* hex_to_base64(char* input)
{
	char* output = malloc(sizeof(char)*SIZE);
	char* buffer = malloc(sizeof(char)*24);
	char* local_copy = malloc(sizeof(char)*8);
	char s;
	int input_length = strlen(input);
	int output_length = 0;
	int i, j, k;
	for(i=0; i<input_length; i+=6) {
		strcpy(buffer, "000000000000222222222222");

		if(i+1 < input_length) {
			local_copy = integer_to_binary(hex_to_integer(input[i], input[i+1]));
			for(j=0; j<8; ++j) buffer[j] = local_copy[j];
		}
		if(i+3 < input_length) {
			local_copy = integer_to_binary(hex_to_integer(input[i+2], input[i+3]));
			for(j=0; j<8; ++j) buffer[8+j] = local_copy[j];
			buffer[16] = '0';
			buffer[17] = '0';
		}
		if(i+5 < input_length) {
			local_copy = integer_to_binary(hex_to_integer(input[i+4], input[i+5]));
			for(j=0; j<8; ++j) buffer[16+j] = local_copy[j];
		}

		for(j=0; j<4; ++j) {
			if(buffer[6*j] == '2') {
				s = pad;
			}
			else {
				local_copy[0] = '0';
				local_copy[1] = '0';
				for(k=0; k<6; ++k) local_copy[2+k] = buffer[6*j+k];
				s = base64_table[binary_to_integer(local_copy)];
			}
			output[output_length++] = s;
		}
	}
	return output;
}

int main(int argc, char* argv[])
{
	char* input = malloc(sizeof(char)*SIZE);
	char* output;

	if(argc > 1)	strcpy(input, argv[1]);
	else {
		printf("Usage: %s \"<input>\"\n", argv[0]);
		return 1;
	}

	output = hex_to_base64(input);
	printf("%s\n", output);
	
	return 0;
}
