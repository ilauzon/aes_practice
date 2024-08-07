#include <stdbool.h>
#include <stdio.h>
#include <bits/types.h>
#include "printbits.h"

#define AES_POLYNOMIAL 0b00011011

__uint32_t multiply_mod_helper(__uint32_t b1) {
    bool msb = b1 >> (sizeof(b1) * 8 - 1);
    printf("msb: %s\n", to_bits(msb, sizeof(msb) * 8));
    b1 <<= 1;
    if (msb) {
        return b1 ^ AES_POLYNOMIAL;   
    } else {
        return b1;
    }
} 

/*
* Multiplies two 32-bit numbers together in GF(2^32).
* For each bit of b2, if it is 1, b1 is right-shifted and XORed with the AES polynomial that bit position's number of times.
* For example, if bit 4 (counting from the right, LSB) of b2 was a 1, then b1 will be XORed with the polynomial 4 times.
* The result will then be XORed with that final value. 
* This process repeats for all bits of b2.
 */
__uint32_t multiply(__uint32_t b1, __uint32_t b2) {
    __uint32_t result = 0;
    for (int i = 0; i < sizeof(b1) * 8; i++) {
        bool is_multiplying = (b2 >> i) & 1;
        printf("is multiplying: %s\n", to_bits(is_multiplying, sizeof(is_multiplying) * 8));
        if (is_multiplying) {
            int multiply_amount = i + 1;
            __uint32_t temp = b1;
            while (multiply_amount--) {
                temp = multiply_mod_helper(temp);
                printf("temp multiply: %s\n", to_bits(temp, sizeof(temp) * 8));
            }
            result ^= temp;
            printf("final multiply: %s\n", to_bits(temp, sizeof(temp) * 8));
            printf("result: %s\n", to_bits(result, sizeof(result) * 8));
        }
    }
    return result;
} 

__uint32_t mod(__uint32_t a, __uint32_t b) {
    return ((a % b) + b) % b;
}

__uint32_t gcd_helper(__uint32_t a, __uint32_t b) {
    __uint32_t quotient = a / b;
    __uint32_t remainder = mod(a, b);
    if (remainder == 0) {
        return b;
    }
    return gcd_helper(b, remainder);
}

__uint32_t gcd(__uint32_t a, __uint32_t b) {
    if (b > a) {
        return gcd_helper(b, a);
    } else {
        return gcd_helper(a, b);
    }
}


/**
 * Finds the multiplicative inverse of a bit pattern num in the finite field
 * GF(2^32) modulo the bit pattern mod.
 * 
 * This is implemented using the Extended Euclid's Algorithm.
 * @param num the starting bit pattern.
 * @param mod the divisor bit pattern. In the case of AES, this is 100011011.
 * @return the multiplicative inverse of num as specified.
 **/
__uint32_t multiplicative_inverse(__uint32_t num, __uint32_t mod) {
	
}