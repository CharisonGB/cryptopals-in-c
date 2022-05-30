#ifndef HEX_BYTE_DUPLEX
#define HEX_BYTE_DUPLEX

#include <stdlib.h>

u_int8_t hex_char_to_byte(const char hexChar)
{
	u_int8_t byte = 0;
	sscanf(&hexChar, "%hhx", &byte);
	return byte;	// We only care about the least significant half of this byte.
}

char byte_to_hex_char(u_int8_t byte)
{
	u_int8_t hexChar[2] = { '\0', '\0' };
	// printf("%hhx\n", byte);
	sprintf(&(*hexChar), "%hhx", byte);
	return *hexChar;	// We only care about the least significant half of this byte.
}

u_int8_t * gen_buffer_from_hex_str(const char * hexStr, int length)
{
	u_int8_t lo, hi;
	u_int8_t * buffer = (u_int8_t *)malloc(length/2);
	
	for(short i = 0; i < length; i+=2)
	{
		hi = hex_char_to_byte(hexStr[length-i-2]);	// Read the hex string backwards in pairs.
		lo = hex_char_to_byte(hexStr[length-i-1]);	// Each converted character only occupies the back half of each byte.
		buffer[(i/2)] = ( (hi << 4) | lo );		// Stuff all the half-bytes into contiguous blocks.
	}
	
	return buffer;
}

const char * gen_hex_str_from_buffer(u_int8_t * buffer, int length)
{
	char lo, hi;
	char * hexStr = (char *)malloc(length*2);
	
	for(short i = 0; i < length*2; i+=2)
	{
		hexStr[i] = byte_to_hex_char(buffer[length-1-(i/2)] >> 4);	// Read the hex string backwards in pairs.		
		hexStr[i+1] = byte_to_hex_char(buffer[length-1-(i/2)] & 0x0F);	// Each converted character only occupies the back half of each byte.
	}
	
	return (const char*)hexStr;
}

u_int8_t * gen_buffer_xor_buffer(u_int8_t * buffer0, u_int8_t * buffer1, int length)
{
	u_int8_t * result = (u_int8_t *)malloc(length);
	
	for(int i = 0; i < length; i++)
		result[i] = buffer0[i] ^ buffer1[i];
	
	return result;
}

#endif // HEX_BYTE_DUPLEX