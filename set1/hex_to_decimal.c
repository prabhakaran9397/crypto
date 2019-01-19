#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

int* hex_to_decimal(char* input)
{
	int* output = malloc(sizeof(int)*SIZE);
	int input_length = strlen(input);
	int i;
	for(i=0; i<input_length; i+=2) {
		if(i+1 < input_length) {
			output[i/2] = hex_to_integer(input[i], input[i+1]);
		}
	}
	return output;
}

char* extract_input(FILE* fp)
{
	int c, i = 0;
	char* data = malloc(sizeof(char)*SIZE);
	while((c = getc(fp)) != EOF)
		if(isxdigit(c))
			data[i++] = c;
	return data;
}

int main(int argc, char* argv[])
{
	char* input = extract_input(argc == 2 ? fopen(argv[1], "r") : stdin);
	int* output = hex_to_decimal(input);

	int size = strlen(input)/2;
	while(size--) printf("%d ", *output++);
	
	return 0;
}
