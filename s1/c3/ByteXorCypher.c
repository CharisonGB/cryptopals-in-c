#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../c2/XBDuplex.h"
#include "BufferGen.h"

int find_max(int * values, int length)
{
	int maxIndex = 0, maxVal = values[maxIndex];
	for(int i = 1; i < length; i++)
	{
		if(values[i] > maxVal)
		{
			maxIndex = i;
			maxVal = values[i];
		}
	}
	
	return maxIndex;
}

const char * gen_reverse_str(const char * str)
{
	int length = strlen(str);
	char * revStr = (char *)malloc(length+1);
	
	for(int i = 0; i < length; i++)
		revStr[i] = str[length-i-1];
	revStr[length] = '\0';
	
	return (const char *)revStr;
}

int main()
{
	const char cyphertext[128] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	
	u_int8_t * cypherBuffer = gen_buffer_from_hex_str(cyphertext, strlen(cyphertext));
	
	u_int8_t * freqBuffer = gen_value_frequency_buffer(cypherBuffer, strlen(cyphertext)/2);
	u_int8_t likelyKey = find_max(freqBuffer, (int)BYTE_MAX);
	free(freqBuffer);
	
	u_int8_t * keyBuffer = gen_filled_buffer(likelyKey, strlen(cyphertext)/2);
	u_int8_t * decypherBuffer = gen_buffer_xor_buffer(cypherBuffer, keyBuffer, strlen(cyphertext)/2);
	free(cypherBuffer);
	free(keyBuffer);
	
	u_int8_t * messageBuffer = gen_replaced_buffer('\0', ' ', decypherBuffer, strlen(cyphertext)/2);
	free(decypherBuffer);
	
	const char * message = gen_reverse_str(messageBuffer);
	free(messageBuffer);
	
	printf("Message: %s\n", message);
	free((void *)message);
	return 0;
}