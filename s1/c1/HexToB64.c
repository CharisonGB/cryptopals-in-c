#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char byte_from_hex_char(const char hexChar)
{
	unsigned char byte = 0;
	sscanf(&hexChar, "%hhx", &byte);
	return byte;	// We only care about the least significant half of this byte.
}

// unsigned short copy_hex_str_to_byte_buff(unsigned char * byteBuff, const char * hexStr, int length)
// {
// 	// unsigned char halfWords[2];
// 	// unsigned char * byteBuff = (unsigned char *)malloc(length/2);
	
// 	for(short i = 0; i < length; i+=2)	// Read two characters at a time.
// 	{
// 		// halfWords[0] = byte_from_hex_char(hexStr[length-i-2]);			// Read the hex string backwards in pairs.
// 		// halfWords[1] = byte_from_hex_char(hexStr[length-i-1]);			// Each converted character only occupies the back half of each byte.
// 		byteBuff[i] = byte_from_hex_char(hexStr[length-i-2]);			// Read the hex string backwards in pairs.
// 		byteBuff[i+1] = byte_from_hex_char(hexStr[length-i-1]);			// Each converted character only occupies the back half of each byte.
// 		byteBuff[(i/2)] = ( (byteBuff[i] << 4) | byteBuff[i+1] );		// Stuff all the half-bytes into contiguous blocks.
// 	}
	
// 	// return byteBuff;
// 	return 1;
// }

unsigned char * mutate_hex_str_to_byte_arr(const char * hexStr, int length)
{
	/*
		hexStr is big-endian if read as a contiguous block of bytes.
		I want to read hexStr as contiguous in future operations, so
		 reverse it here.
	*/
	
	unsigned char * hexBuff = (unsigned char *)(&(*hexStr));
	unsigned char * byteArr = (unsigned char *)malloc(length);
	memcpy(byteArr, hexBuff, length);
	
	// FIXME: The null terminator is the only reason this doesnt buffer overflow with odd-length strings.
	for(short i = 0; i < length; i+=2)	// Read two characters at a time.
	{
		hexBuff[i] = byte_from_hex_char(byteArr[length-i-2]);			// Read the byteArr backwards in pairs.
		hexBuff[i+1] = byte_from_hex_char(byteArr[length-i-1]);			// Each converted character only occupies the back half of each byte.
		hexBuff[(i/2)] = ( (hexBuff[i] << 4) | hexBuff[i+1] );	// Stuff all the half-bytes into contiguous blocks.
	}
	
	free(byteArr);
	return hexBuff;
}

char b64_char_from_byte(const unsigned char byte)
{
	const char b64Alphabet[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	// https://datatracker.ietf.org/doc/html/rfc4648#page-5
	// Pad character '=' not included.
	return b64Alphabet[(short)byte];
}

// unsigned short copy_byte_buff_to_b64_str(char * b64Str, unsigned char * byteBuff, int length)
// {
// 	const short B64_PHRASE_BYTES = 3;
// 	const short B64_PHRASE_CHARS = 4;
// 	const short NUM_B64_PHRASES = (length+2)/B64_PHRASE_BYTES;
	
// 	unsigned int * phraseByteArr = (unsigned int * )malloc(NUM_B64_PHRASES);
	
// 	for(short i = 0; i < length; i+=B64_PHRASE_BYTES)
// 		phraseByteArr[i/B64_PHRASE_BYTES] = *((int *)(byteBuff+i));
	
// 	const unsigned char B64_CHAR_BITMASK = 0x3F;
// 	const short B64_CHAR_BITS = 6;
// 	const short TOTAL_B64_CHARS = NUM_B64_PHRASES * B64_PHRASE_CHARS;
	
// 	for(short i = 0; i < TOTAL_B64_CHARS; i++)	// FIXME: This loop should run more than on iteration per byte, since b64 characters are smaller than a byte.
// 	{
// 		byteBuff[TOTAL_B64_CHARS-1-i] = B64_CHAR_BITMASK & phraseByteArr[i/B64_PHRASE_CHARS];
// 		phraseByteArr[i/B64_PHRASE_CHARS] >>= B64_CHAR_BITS;
// 		b64Str[TOTAL_B64_CHARS-1-i] = b64_char_from_byte(byteBuff[TOTAL_B64_CHARS-1-i]);
// 	}
	
// 	free(phraseByteArr);
// 	return 1;
// }

const char * mutate_byte_arr_to_b64_str(unsigned char * byteArr, int length)
{
	const short B64_PHRASE_BYTES = 3;
	const short B64_PHRASE_CHARS = 4;
	const short NUM_B64_PHRASES = (length+2)/B64_PHRASE_BYTES;
	
	unsigned int * phraseByteArr = (unsigned int * )malloc(NUM_B64_PHRASES);
	
	for(short i = 0; i < length; i+=B64_PHRASE_BYTES)
		phraseByteArr[i/B64_PHRASE_BYTES] = *((int *)(byteArr+i));
	
	// TODO: Read b64 chars from phraseByteArr
	const unsigned char B64_CHAR_BITMASK = 0x3F;
	const short B64_CHAR_BITS = 6;
	const short TOTAL_B64_CHARS = NUM_B64_PHRASES * B64_PHRASE_CHARS;
	unsigned char temp;
	for(short i = 0; i < TOTAL_B64_CHARS; i++)	// FIXME: This loop should run more than on iteration per byte, since b64 characters are smaller than a byte.
	{
		byteArr[TOTAL_B64_CHARS-1-i] = B64_CHAR_BITMASK & phraseByteArr[i/B64_PHRASE_CHARS];
		phraseByteArr[i/B64_PHRASE_CHARS] >>= B64_CHAR_BITS;
		// byteArr[TOTAL_B64_CHARS-1-i] = B64_CHAR_BITMASK & ( phraseByteArr[i/B64_PHRASE_CHARS] >> (B64_CHAR_BITS*(i%B64_PHRASE_CHARS)) );
		byteArr[TOTAL_B64_CHARS-1-i] = b64_char_from_byte(byteArr[TOTAL_B64_CHARS-1-i]);
	}
	
	free(phraseByteArr);
	const char * b64Str = (char*)&(*byteArr);
	return b64Str;
}

// NOTE: System is little-endian
int main()
{
	const char sourceStr[256] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	// const char sourceStr[256] = "414243";
	// printf("We need to convert 0x%s to base 64.\n", sourceStr);
	// char hexNumStr[6*sizeof(char)] = "000001";
	
	// printf("Let try converting %s to an int by retrieveing it from sscanf.\n", hexNumStr);
	// printf("Got %d!\n", byte_from_hex_char(hexNumStr[0]));
	
	// unsigned char buff[4*sizeof(char)];
	// short success = byte_arr_from_hex_str(hexNumStr, buff);
	// printf("Padded buffer came back with status %d\nReading the padded buffer: %d, %d\n", success, buff[0], buff[1]);
	
	// unsigned char buff[256];
	// char b64Str[256];
	
	unsigned char * buff = mutate_hex_str_to_byte_arr(sourceStr, strlen(sourceStr));
	// copy_hex_str_to_byte_buff(buff, sourceStr, strlen(sourceStr));
	printf("%s\n", buff);	// Decoded string representation
	
	const char * b64Str = mutate_byte_arr_to_b64_str(buff, strlen(sourceStr));
	// copy_byte_buff_to_b64_str(b64Str, buff, (strlen(sourceStr)/2));
	printf("%s\n", b64Str);
	
	return 0;
}