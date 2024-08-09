#include <stdio.h>
#include <bits/types.h>
#include "aes.h"

int main() {
	// aes_encrypt128("a");

	__uint8_t b1 = 0b00000001;
	__uint8_t b2 = 0b00000011;
	printf("modular multiplication of %d and %d is %d\n", b1, b2, multiply(b1, b2));

	long a = 161;
	long b = 28;
	printf("gcd of %ld and %ld is %ld\n", a, b, gcd(a, b));

	printf("MI Test: ");
	eea_MI(a, b);
}