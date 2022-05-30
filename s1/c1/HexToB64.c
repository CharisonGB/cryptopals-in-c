#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u_int8_t hex_char_to_byte(const char hexChar)
{
	u_int8_t byte = 0;
	sscanf(&hexChar, "%hhx", &byte);
	return byte;	// We only care about the least significant half of this byte.
}

u_int8_t * make_buffer_from_hex_str(const char * hexStr, int length)
{
	u_int8_t onesPlace, sixteensPlace;
	u_int8_t * buffer = (u_int8_t *)malloc(length/2);
	
	for(short i = 0; i < length; i+=2)
	{
		sixteensPlace = hex_char_to_byte(hexStr[length-i-2]);		// Read the hex string backwards in pairs.
		onesPlace = hex_char_to_byte(hexStr[length-i-1]);			// Each converted character only occupies the back half of each byte.
		buffer[(i/2)] = ( (sixteensPlace << 4) | onesPlace );		// Stuff all the half-bytes into contiguous blocks. Bytes must be big-endian!
	}
	
	return buffer;
}

char byte_to_b64_char(const u_int8_t byte)
{
	const char b64Alphabet[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	// https://datatracker.ietf.org/doc/html/rfc4648#page-5
	// Pad character '=' not included.
	return b64Alphabet[byte];
}

const char * make_b64_str_from_buffer(u_int8_t * buffer, int length)
{
	const short B64_PHRASE_BYTES = 3;
	const short B64_PHRASE_CHARS = 4;
	const short NUM_B64_PHRASES = (length+2)/B64_PHRASE_BYTES;
	
	u_int32_t * phraseByteArr = (u_int32_t *)malloc(NUM_B64_PHRASES * sizeof(u_int32_t));
	
	for(short i = 0; i < length; i+=B64_PHRASE_BYTES)
		phraseByteArr[i/B64_PHRASE_BYTES] = *((u_int32_t *)(buffer+i));
	
	const u_int8_t B64_CHAR_BITMASK = 0x3F;
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
	
	u_int8_t * buff = make_buffer_from_hex_str(sourceStr, strlen(sourceStr));
	// printf("%s\n", buff);	// Decoded string representation (reversed string)
	
	const char * b64Str = make_b64_str_from_buffer(buff, strlen(sourceStr)/2);
	printf("%s\n", b64Str);
	
	free(buff);
	free((void *)b64Str);
	
	return 0;
}