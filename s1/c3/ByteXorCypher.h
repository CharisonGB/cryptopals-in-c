#ifndef BYTE_XOR_CYPHER
#define BYTE_XOR_CYPHER

#include <stdlib.h>

const size_t BYTE_MAX = 256;

int * CalculateByteFreq(unsigned char * buffer, int length)
{
	int * freqBuffer = (int *)malloc(BYTE_MAX*sizeof(int));
	
	for(int i = 0; i < length; i++)
		freqBuffer[buffer[i]]++;
	
	return freqBuffer;
}

#endif // BYTE_XOR_CYPHER