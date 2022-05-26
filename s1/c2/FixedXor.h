#ifndef FIXED_XOR_H
#define FIXED_XOR_H

unsigned char hex_char_to_byte(const char hexChar)
{
	unsigned char byte = 0;
	sscanf(&hexChar, "%hhx", &byte);
	return byte;	// We only care about the least significant half of this byte.
}

char byte_to_hex_char(unsigned char byte)
{
	unsigned char hexChar[2] = { '\0', '\0' };
	// printf("%hhx\n", byte);
	sprintf(&(*hexChar), "%hhx", byte);
	return *hexChar;	// We only care about the least significant half of this byte.
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

const char * make_hex_str_from_byte_buff(unsigned char * byteBuff, int length)
{
	char lo, hi;
	char * hexStr = (char *)malloc(length*2);
	
	for(short i = 0; i < length*2; i+=2)
	{
		hexStr[i] = byte_to_hex_char(byteBuff[length-1-(i/2)] >> 4);	// Read the hex string backwards in pairs.		
		hexStr[i+1] = byte_to_hex_char(byteBuff[length-1-(i/2)] & 0x0F);	// Each converted character only occupies the back half of each byte.
	}
	
	return (const char*)hexStr;
}

#endif // FIXED_XOR_H