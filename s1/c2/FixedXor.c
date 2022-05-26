#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FixedXor.h"

int main()
{
	// TODO
	const char hexStrIn[8] = "ABCDEF";
	
	unsigned char * buffer = make_byte_buff_from_hex_str(hexStrIn, strlen(hexStrIn));
	const char * hexStrOut = make_hex_str_from_byte_buff(buffer, strlen(hexStrIn)/2);
	
	printf("Expected: %s\nGot: %s\n", hexStrIn, hexStrOut);
	
	free(buffer);
	free((void *)hexStrOut);
	return 0;
}