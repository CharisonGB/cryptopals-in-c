#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char hex_char_to_byte(const char hexChar)
{
	unsigned char byte = 0;
	sscanf(&hexChar, "%hhx", &byte);
	return byte;	// We only care about the least significant half of this byte.
}

unsigned char * make_byte_buff_from_hex_str(const char * hexStr, int length)
{
	unsigned char lo, hi;
	unsigned char * byteBuff = (unsigned char *)malloc(length/2);
	
	for(short i = 0; i < length; i+=2)
	{
		hi = hex_char_to_byte(hexStr[length-i-2]);	// Read the hex string backwards in pairs.
		lo = hex_char_to_byte(hexStr[length-i-1]);	// Each converted character only occupies the back half of each byte.
		byteBuff[(i/2)] = ( (hi << 4) | lo );		// Stuff all the half-bytes into contiguous blocks.
	}
	
	return byteBuff;
}

char byte_to_b64_char(const unsigned char byte)
{
	const char b64Alphabet[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	// https://datatracker.ietf.org/doc/html/rfc4648#page-5
	// Pad character '=' not included.
	return b64Alphabet[(short)byte];
}

const char * make_b64_str_from_byte_buff(unsigned char * byteBuff, int length)
{
	const short B64_PHRASE_BYTES = 3;
	const short B64_PHRASE_CHARS = 4;
	const short NUM_B64_PHRASES = (length+2)/B64_PHRASE_BYTES;
	
	unsigned int * phraseByteArr = (unsigned int *)malloc(NUM_B64_PHRASES * sizeof(int));
	
	for(short i = 0; i < length; i+=B64_PHRASE_BYTES)
		phraseByteArr[i/B64_PHRASE_BYTES] = *((unsigned int *)(byteBuff+i));
	
	const unsigned char B64_CHAR_BITMASK = 0x3F;
	const short B64_CHAR_BITS = 6;
	const short TOTAL_B64_CHARS = NUM_B64_PHRASES * B64_PHRASE_CHARS;
	
	char * b64Str = (char *)malloc(TOTAL_B64_CHARS);
	
	for(short i = 0; i < TOTAL_B64_CHARS; i++)
	{
		b64Str[TOTAL_B64_CHARS-1-i] = B64_CHAR_BITMASK & phraseByteArr[i/B64_PHRASE_CHARS];
		phraseByteArr[i/B64_PHRASE_CHARS] >>= B64_CHAR_BITS;
		b64Str[TOTAL_B64_CHARS-1-i] = byte_to_b64_char(b64Str[TOTAL_B64_CHARS-1-i]);
	}
	
	free(phraseByteArr);
	return (const char *)b64Str;
}

int main()
{
	const char sourceStr[256] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	
	unsigned char * buff = make_byte_buff_from_hex_str(sourceStr, strlen(sourceStr));
	// printf("%s\n", buff);	// Decoded string representation
	
	const char * b64Str = make_b64_str_from_byte_buff(buff, strlen(sourceStr)/2);
	printf("%s\n", b64Str);
	
	free(buff);
	free((void *)b64Str);
	
	return 0;
}