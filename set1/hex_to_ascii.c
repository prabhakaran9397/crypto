#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10000

int char_to_int(char c) {
	return c-'0';
}

int hex_to_integer(char hex_0, char hex_1)
{
	int first_digit	 = hex_0 > '9' ? hex_0-'a'+10 : char_to_int(hex_0);
	int second_digit = hex_1 > '9' ? hex_1-'a'+10 : char_to_int(hex_1);
	int integer = first_digit*16 + second_digit;
	return integer;
}

char* hex_to_ascii(char* input)
{
	char* output = malloc(sizeof(char)*SIZE);
	int input_length = strlen(input);
	int i;
	for(i=0; i<input_length; i+=2) {
		if(i+1 < input_length) {
			output[i/2] = hex_to_integer(input[i], input[i+1]);
		}
	}
	return output;
}

int main(int argc, char* argv[])
{
	char* input = malloc(sizeof(char)*SIZE);
	char* output;

	if(argc > 1)	strcpy(input, argv[1]);
	else		scanf("%s", input);

	output = hex_to_ascii(input);
	printf("%s", output);
	
	return 0;
}
