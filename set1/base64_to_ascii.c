#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 10000
#define ISBASE64(c) isalnum(c) || strchr("+/=", c)

int char_to_int(char c) {
	return c-'0';
}

char int_to_char(int i) {
	return i+'0';
}

int base64_to_int(char c) {
	if(isupper(c)) return c-'A';
	if(islower(c)) return c-'a'+26;
	if(isdigit(c)) return c-'0'+52;
	if(c == '+')   return 62;
	if(c == '/')   return 63;	
}

char* extract_base64(FILE* fp)
{
	int c, i = 0;
	char* data = malloc(sizeof(char)*SIZE);
	while((c = getc(fp)) != EOF)
		if(ISBASE64(c))
			data[i++] = c;
	return data;
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

char* integer_to_binary(int integer)
{
	char* binary = malloc(sizeof(char)*6);
	strcpy(binary, "000000");
	int i = 5;
	while(integer) {
		binary[i--] = int_to_char(integer%2);
		integer /= 2;
	}
	return binary;
}

void base64_to_ascii(char* input, char* output, int* length)
{
	char* buffer = malloc(sizeof(char)*24);
	char* local_copy = malloc(sizeof(char)*8);
	int input_length = strlen(input);
	int output_length = 0;
	int i;
	for(i=0; i<input_length; i++) {
		strcat(buffer, integer_to_binary(base64_to_int(input[i])));
		if(strlen(buffer) > 7) {
			strncpy(local_copy, buffer, 8);
			output[output_length++] = binary_to_integer(local_copy);
			memmove(buffer, buffer+8, strlen(buffer)-7);
		}
	}
	*length = output_length;
}


int main(int argc, char* argv[])
{
	char* input  = extract_base64(argc == 2 ? fopen(argv[1], "r") : stdin);
	char* output = malloc(sizeof(char)*SIZE);
	int len = 0;
	base64_to_ascii(input, output, &len);

	while(len--) putchar(*output++);

	return 0;
}
