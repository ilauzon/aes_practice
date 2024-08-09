#include <stdio.h>
#include <bits/types.h>
#include "aes.h"

void test_multiplication() {
	__uint8_t b1 = 0b00000001;
	__uint8_t b2 = 0b00000011;
	printf("modular multiplication of %d and %d is %d\n", b1, b2, multiply(b1, b2));
}

void test_gcd() {
	long a = 161;
	long b = 28;
	printf("gcd of %ld and %ld is %ld\n", a, b, gcd(a, b));
}

void test_eea() {
	long a = 161;
	long b = 28;
	printf("EEA calculation of a = %ld and b = %ld: ", a, b);
	__int64_t* result = eea_full(a, b);
	printf("s = %ld, t = %ld\n", result[0], result[1]);
}

void test_mi() {
	long num = 11;
	long mod = 26;
	__int64_t mi = modular_MI(num, mod);
	if (mi == -1) {
		printf("No modular multiplicative inverse exists for %ld in mod %ld\n", num, mod);
	} else {
		printf("Modular multiplicative inverse of %ld in mod %ld is %ld\n", num, mod, mi);
	}
}

int main() {
	test_mi();
	return 0;
}