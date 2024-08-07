#include <stdlib.h>
char* to_bits(__uint64_t num, int bits) {
	char* resultant_string = malloc(bits);
	int counter = 0;

	int starting_shift = bits;
	while (starting_shift--) {
		int bit = (num >> starting_shift) & 1;
		resultant_string[counter++] = bit + '0';
	}
	return resultant_string;
}