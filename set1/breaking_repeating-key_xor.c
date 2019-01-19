#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 10000

int extract_input(FILE* fp, int* data)
{
	int i=0;
	while(fscanf(fp, "%d", &data[i++]) != EOF);
	return i-1;
}

int edit_distance(int* a, int* b, int len)
{
	int dist = 0;
	while(--len>-1) dist += __builtin_popcount(a[len]^b[len]);
	return dist;
}

int main(int argc, char* argv[])
{
	int* input = malloc(sizeof(char)*SIZE);
	int  size = extract_input(argc == 2 ? fopen(argv[1], "r") : stdin, input);
	
	int tem1[] = {116, 104, 105, 115, 32, 105, 115, 32, 97, 32, 116, 101, 115, 116,};
	int tem2[] = {119, 111, 107, 107, 97, 32, 119, 111, 107, 107, 97, 33, 33, 33};

	int i = edit_distance(tem1, tem2, 14);
	printf("%d\n", i);

	return 0;
}
