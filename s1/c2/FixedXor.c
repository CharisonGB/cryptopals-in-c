#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XBDuplex.h"

int main()
{
	const char protagonist[64] = "1c0111001f010100061a024b53535009181c";
	const char antagonist[64] = "686974207468652062756c6c277320657965";
	
	u_int8_t * proBuffer = make_buffer_from_hex_str(protagonist, strlen(protagonist));
	u_int8_t * antBuffer = make_buffer_from_hex_str(antagonist, strlen(antagonist));
	
	u_int8_t * resBuffer = buffer_xor_buffer(proBuffer, antBuffer, strlen(protagonist)/2);
	
	const char * resolution = make_hex_str_from_buffer(resBuffer, strlen(protagonist)/2);
	printf("%s\nxor\n%s\n=\n%s\n", protagonist, antagonist, resolution);
	// printf("Output string:\n%s\n", resolution);
	
	free(proBuffer);
	free(antBuffer);
	free(resBuffer);
	free((void *)resolution);
	return 0;
}