#include <stdio.h>
#include <stdlib.h>

int main()
{
	const char sourceString[256] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	printf("We need to convert 0x%s to base 64.\n", sourceString);
	
	return 0;
}