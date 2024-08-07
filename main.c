#include <stdio.h>
#include <bits/types.h>
#include "aes.h"

int main() {
	// aes_encrypt128("a");
	__uint8_t b1 = 0b00000001;
	__uint8_t b2 = 0b00000011;
	__uint8_t b3 = 45;
	__uint8_t b4 = 105;
	// printf("%d %d %d\n", b1, b2, multiply(b1, b2));
	printf("gcd of %d and %d is %d\n", b3, b4, gcd(b3, b4));
}