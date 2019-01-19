#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 10000
#define MAX_GUESS 40

struct weighted {
	int value;
	double weight;
};
typedef struct weighted weighted;

int extract_input(FILE* fp, int* data)
{
	int i=0;
	while(fscanf(fp, "%d", &data[i++]) != EOF);
	return i-1;
}

int print_array(int* arr, int len)
{
	int i;
	putchar('[');
	for(i=0; i<len; ++i)
		printf("%3d ", arr[i]);
	putchar(']');
}

int edit_distance(int* a, int* b, int len)
{
	int dist = 0;
	while(--len>-1) dist += __builtin_popcount(a[len]^b[len]);
	return dist;
}

void sort_weighted(weighted k[])
{
	int i, j;
	weighted t;
	for(i=0; i<MAX_GUESS; ++i)
		for(j=i+1; j<MAX_GUESS; ++j)
			if(k[i].weight > k[j].weight)
				t = k[i], k[i] = k[j], k[j] = t;
}

int guess_keysize(int* input, int input_len)
{
	weighted keys[MAX_GUESS+1] = {{0, 100}, {1, 100}};
	int kl, i, n;
	double ed;
	for(kl=2; kl<=MAX_GUESS; ++kl) {
		for(i=ed=0; i+2*kl<=input_len; i+=2*kl)
			ed += edit_distance(input+i, input+i+kl, kl)/(1.0*kl);
		keys[kl].value = kl;
		keys[kl].weight = (ed*2*kl)/input_len;
	}
	sort_weighted(keys);
	return keys[0].value;
}

int main(int argc, char* argv[])
{
	int* input     = malloc(sizeof(int)*SIZE);
	int input_len  = extract_input(argc == 2 ? fopen(argv[1], "r") : stdin, input);
	
	//Can be extended to return multiple keysizes
	int keysize = guess_keysize(input, input_len);

	printf("%d\n", keysize);	

	return 0;
}
