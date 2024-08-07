#include <stdio.h>
#include <bits/types.h>
#include "aes.h"

int main() {
	// aes_encrypt128("a");
	__uint8_t b1 = 0b00000001;
	__uint8_t b2 = 0b00000011;
	printf("%d %d %d\n", b1, b2, multiply(b1, b2));
}