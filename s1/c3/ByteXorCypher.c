#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ByteXorCypher.h"
#include "../c2/XBDuplex.h"

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

unsigned char * make_filled_buffer(unsigned char val, int length)
{
	unsigned char * buffer = (unsigned char *)malloc(length);
	
	for(int i = 0; i < length; i++)
		buffer[i] = val;
	
	return buffer; 
}

void replace_byte(unsigned char source, unsigned char dest, unsigned char * buffer, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(buffer[i] == source)
		{
			buffer[i] = dest;
		}
	}
	
	return;
}

const char * make_reverse_str(const char * str)
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
	
	unsigned char * buffer = make_buffer_from_hex_str(cyphertext, strlen(cyphertext));
	int * byteFreqBuff = CalculateByteFreq(buffer, strlen(cyphertext)/2);
	
	int likelyKey = find_max(byteFreqBuff, (int)BYTE_MAX);
	
	unsigned char * keyBuffer = make_filled_buffer(likelyKey, strlen(cyphertext)/2);
	unsigned char * messageBuffer = buffer_xor_buffer(buffer, keyBuffer, strlen(cyphertext)/2);
	replace_byte(0x00, 0x20, messageBuffer, strlen(cyphertext)/2);
	
	const char * message = make_reverse_str(messageBuffer);
	
	printf("Cyphertext: %s%c\n", buffer, '\0');
	printf("Message: %s\n", message);
	
	free(buffer);
	free(byteFreqBuff);
	free(keyBuffer);
	free(messageBuffer);
	free((void *)message);
	return 0;
}