#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10000

char int_to_char(int i) {
	return i+'0';
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

char* ascii_to_hex(char* input, int len)
{
	char* output = malloc(sizeof(char)*SIZE);
	char* local_copy = malloc(sizeof(char)*2);
	int i;
	for(i=0; i<len; i++) {
		local_copy = integer_to_hex(input[i]);
		output[2*i]   = local_copy[0];
		output[2*i+1] = local_copy[1];
	}
	return output;
}

extract_input(FILE* fp, char* data, int* len)
{
	int c, i = 0;
	while((c = getc(fp)) != EOF)
		data[i++] = c;
	*len = i-1;
}

int main(int argc, char* argv[])
{
	char* input = malloc(sizeof(char)*SIZE);
	int len;
	extract_input(argc == 2 ? fopen(argv[1], "r") : stdin, input, &len);
	char* output;

	output = ascii_to_hex(input, len);
	printf("%s", output);
	
	return 0;
}
