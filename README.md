# My C Attempt at the [Cryptopals Challenges](https://cryptopals.com/)

## The Fun Part

### Set 1 / Challenge 1
	
	Approach:
	* Read the input string in pairs.
		* Interpret each pair as hex characters.
		* Move each pair of hex values into a contiguous byte.
	* Group bytes into 3-byte groups.
		* Store each 3-byte group in a temp integer.
		* Ignore the last byte in each temp integer.
	* Fill the output string by reading 4 base-64 characters from each 3-byte group.
	
	Notes:
	* My system is little-endian.
	
## Project Conventions

	File Names:	PascalCase
	Functions:	snake_case
	Variables:	camelCase
	constants:	SCREAMING_SNAKE_CASE