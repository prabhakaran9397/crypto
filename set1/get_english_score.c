#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10000

float get_char_score(char c)
{
	float score_card[] = {	8.167, 1.492,
		2.782, 4.253, 12.702, 2.228, 2.015,
		6.094, 6.966, 0.153, 0.772, 4.025,
		2.406, 6.749, 7.507, 1.929, 0.095,
		5.987, 6.327, 9.056, 2.758, 0.978,
		2.360, 0.150, 1.974, 0.074
	};
	if(c == ' ')	return 13.0;
	if(isupper(c))	c ^= 32;
	if(islower(c))	return score_card[c - 'a'];
	return 0;	 
}

float get_english_score(char* input, int len)
{
	float score = 0;
	int i;
	for(i=0; i<len; i++) {
		score += get_char_score(input[i]);
	}
	return score;
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

	float output = get_english_score(input, len);
	printf("%.3f\n", output);
	
	return 0;
}
