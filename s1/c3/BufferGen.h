#ifndef BUFFER_GEN_H
#define BUFFER_GEN_H

#include <stdlib.h>

const size_t BYTE_MAX = 256;

u_int32_t * gen_value_frequency_buffer(u_int8_t * buffer, int length)
{
	u_int32_t * freqBuffer = (u_int32_t *)malloc(BYTE_MAX*sizeof(u_int32_t));
	
	for(int i = 0; i < length; i++)
		freqBuffer[buffer[i]]++;
	
	return freqBuffer;
}

u_int8_t * gen_filled_buffer(u_int8_t val, int length)
{
	u_int8_t * buffer = (u_int8_t *)malloc(length);
	
	for(int i = 0; i < length; i++)
		buffer[i] = val;
	
	return buffer; 
}

u_int8_t replace_byte(u_int8_t target, u_int8_t replacement, u_int8_t byte)
{
	if(byte == target)
		return replacement; 
	
	return byte;
}

u_int8_t * gen_replaced_buffer(u_int8_t target, u_int8_t replacement, u_int8_t * buffer, int length)
{
	u_int8_t * replacedBuffer = (u_int8_t *)malloc(length);
	
	for(int i = 0; i < length; i++)
		replacedBuffer[i] = replace_byte(target, replacement, buffer[i]);
	
	return replacedBuffer;
}

#endif // BUFFER_GEN_H