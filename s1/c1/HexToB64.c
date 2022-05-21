#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char byte_from_hex_char(const char hexChar)
{
	unsigned char byte = 0;
	sscanf(&hexChar, "%hhx", &byte);
	return byte;	// We only care about the least significant half of this byte.
}

// int byte_arr_from_hex_str(const char * hexStr, unsigned char * byteArr)
// {
// 	short length = strlen(hexStr);
	
// 	for(short i = 0; i < length; i++)
// 		byteArr[i] = byte_from_hex_char(hexStr[i]);
	
// 	unsigned char buffContiguous[(length+1)/2];
	
// 	for(short i = 0; i < length; i+=2)
// 	{
// 		buffContiguous[(i/2)] = ( byteArr[i] | (byteArr[i+1] << 4) );	// Stuff all the half-bytes into contiguous blocks.
// 		byteArr[i] = buffContiguous[(i/2)];
// 	}
	
// 	return 1;	// True
// }

// TODO: Try mutating the input hexStr by reinterpreting with different pointers.
//	Input hex sting pointer, mutate to byte list, get out unsigned char buffer.
//	mutate_hex_str_to_byte_arr()
unsigned char * mutate_hex_str_to_byte_arr(const char * hexStr, int length)
{
	unsigned char * byteArr = (unsigned char *)(&(*hexStr));
	
	// FIXME: The null terminator is the only reason this doesnt buffer overflow with odd-length strings.
	for(short i = 0; i < length; i+=2)	// Read two characters at a time.
	{
		byteArr[i] = byte_from_hex_char(hexStr[i]);				// Use the array itself as temp storage.
		byteArr[i+1] = byte_from_hex_char(hexStr[i+1]);			// Each converted character only occupies the back half of each byte.
		byteArr[(i/2)] = ( (byteArr[i] << 4) | byteArr[i+1] );	// Stuff all the half-bytes into contiguous blocks.
		// Each byte should be big-endian, even though system is little-endian.
	}
	
	return byteArr;
}

char b64_char_from_byte(const unsigned char byte)
{
	const char b64Alphabet[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	// https://datatracker.ietf.org/doc/html/rfc4648#page-5
	// Pad character '=' not included.
	return b64Alphabet[(short)byte];
}

const char * mutate_byte_arr_to_b64_str(unsigned char * byteArr, int length)
{
	const short B64_PHRASE_BYTES = 3;
	const short B64_PHRASE_CHARS = 4;
	const short NUM_B64_PHRASES = (length+2)/B64_PHRASE_BYTES;
	
	unsigned int * phraseByteArr = (unsigned int * )malloc(NUM_B64_PHRASES);
	
	for(short i = 0; i < length; i+=B64_PHRASE_BYTES)
		phraseByteArr[i/B64_PHRASE_BYTES] = *((int *)(byteArr+i));
	
	// TODO: Read b64 chars from phraseByteArr
	const short B64_CHAR_BITS = 6;
	const unsigned char B64_CHAR_BITMASK = 0x3F;
	unsigned char temp;
	for(short i = 0; i < (NUM_B64_PHRASES*B64_PHRASE_CHARS); i++)	// FIXME: This loop should run more than on iteration per byte, since b64 characters are smaller than a byte.
	{
		temp = B64_CHAR_BITMASK & phraseByteArr[i/B64_PHRASE_BYTES];
		phraseByteArr[i/B64_PHRASE_CHARS] >>= B64_CHAR_BITS;
		// temp = B64_CHAR_BITMASK & ( phraseByteArr[i/B64_PHRASE_BYTES] >> (B64_CHAR_BITS*(i%B64_PHRASE_BYTES)) );
		// byteArr[i] = b64_char_from_byte(temp);
	}
	
	free(phraseByteArr);
	const char * b64Str = (char*)&(*byteArr);
	return b64Str;
}

// NOTE: System is little-endian
int main()
{
	// const char sourceStr[256] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	const char sourceStr[256] = "0F0F0F";
	// printf("We need to convert 0x%s to base 64.\n", sourceStr);
	// char hexNumStr[6*sizeof(char)] = "000001";
	
	// printf("Let try converting %s to an int by retrieveing it from sscanf.\n", hexNumStr);
	// printf("Got %d!\n", byte_from_hex_char(hexNumStr[0]));
	
	// unsigned char buff[4*sizeof(char)];
	// short success = byte_arr_from_hex_str(hexNumStr, buff);
	// printf("Padded buffer came back with status %d\nReading the padded buffer: %d, %d\n", success, buff[0], buff[1]);
	
	unsigned char * buff = mutate_hex_str_to_byte_arr(sourceStr, strlen(sourceStr));
	printf("%s\n", buff);	// Decoded string representation
	
	// const char * b64Str = mutate_byte_arr_to_b64_str(buff, (strlen(hexNumStr)/2));
	const char * b64Str = mutate_byte_arr_to_b64_str(buff, (strlen(sourceStr)/2));
	printf("%s\n", b64Str);
	
	return 0;
}