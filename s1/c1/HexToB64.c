#include <stdio.h>
#include <stdlib.h>

int hex_int_from_str(char * str)
{
	// Test function to make my life easier.
	
	int hexNum = 0;
	sscanf(str, "%x", &hexNum);
	
	return hexNum;
}

int main()
{
	// const char sourceString[256] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	// printf("We need to convert 0x%s to base 64.\n", sourceString);
	char hexNumStr[4*sizeof(char)] = "10";
	
	printf("Let try converting %s to an int by retrieveing it from sscanf.\n", hexNumStr);
	printf("Got %d!\n", hex_int_from_str(hexNumStr));
	
	return 0;
}