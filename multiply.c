#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printbits.h"

#define AES_POLYNOMIAL 0b00011011
#define SIZE 10

typedef __int64_t i64;

__uint32_t multiply_mod_helper(__uint32_t b1) {
    bool msb = b1 >> (sizeof(b1) * 8 - 1);
    // printf("msb: %s\n", to_bits(msb, sizeof(msb) * 8));
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
        // printf("is multiplying: %s\n", to_bits(is_multiplying, sizeof(is_multiplying) * 8));
        if (is_multiplying) {
            int multiply_amount = i + 1;
            __uint32_t temp = b1;
            while (multiply_amount--) {
                temp = multiply_mod_helper(temp);
                // printf("temp multiply: %s\n", to_bits(temp, sizeof(temp) * 8));
            }
            result ^= temp;
            // printf("final multiply: %s\n", to_bits(temp, sizeof(temp) * 8));
            // printf("result: %s\n", to_bits(result, sizeof(result) * 8));
        }
    }
    return result;
} 

i64 mod(i64 a, i64 b) {
    i64 result = ((a % b) + b) % b;
    // printf("mod of %ld and %ld is %ld\n", a, b, result);
    return result;
}

i64 gcd_helper(i64 a, i64 b) {
    if (b == 0) return labs(a);

    i64 quotient = a / b;
    i64 remainder = mod(a, b);
    if (remainder == 0) {
        return b < 0 ? -b : b;
    }
    return gcd_helper(b, remainder);
}

i64 gcd(i64 a, i64 b) {
    if (b > a) {
        return gcd_helper(b, a);
    } else {
        return gcd_helper(a, b);
    }
}

typedef struct {
    i64 a, b, q, r, s1, s2, s3, t1, t2, t3;
} eea_array;

typedef struct {
    i64 s, t;
} eea_result;

eea_array* eea_init(i64 a, i64 b) {
    eea_array* obj = malloc(sizeof *obj);
    if (!obj) {
        perror("Allocation failed");
        abort();
    }

    memcpy(obj, &(eea_array) {
        .a = a,
        .b = b,
        .s1 = 1,
        .s2 = 0,
        .s3 = 1,
        .t1 = 0,
        .t2 = 1,
    }, sizeof *obj);

    if (b != 0) {
        obj->q = a / b;
        obj->r = mod(a, b);
        obj->t3 = -obj->q;
    }

    return obj;
}
    

void eea_next(eea_array* arr) {
    arr->a = arr->b;
    arr->b = arr->r;

    arr->s1 = arr->s2;
    arr->s2 = arr->s3;

    arr->t1 = arr->t2;
    arr->t2 = arr->t3;

    if (arr->b == 0) return; // avoid dividing by zero

    arr->q = arr->a / arr->b;
    arr->r = mod(arr->a, arr->b);
    arr->s3 = arr->s1 - arr->q * arr->s2;
    arr->t3 = arr->t1 - arr->q * arr->t3;
}

/*
Finds the coefficients resulting from the Extended Euclidean Algorithm for
finding the greatest common denominator of two numbers.

Input: the two numbers a and b of the equation below.
Output: a pointer to three 64-bit integers, with `[0]` being the
coefficient `s`, `[1]` being the coefficient `t`, and `[2]` being the gcd in the equation:

`s * a + t * b = gcd(a, b)`
*/
i64* eea_full(i64 a, i64 b) {
    eea_array* array = eea_init(a, b);

    // when b, the divisor, is zero, we are done.
    while (array->b != 0) {
        eea_next(array);
    }

    /*
    we are trying to find the values s, t, and gcd(a, b) in the following eq'n:
    |s * a + t * b| = gcd(a, b)
    in our case, the s and t we are looking for are s1 and t1 after the last
    iteration. the gcd would be the value of a after the last iteration.
    Here is the check:
    */
    i64 lhs = array->s1 * a + array->t1 * b;
    i64 rhs = array->a;
    printf("a = %ld\nb = %ld\ns = %ld\nt = %ld\ngcd = %ld\n", a, b, array->s1, array->t1, array->a);
    if (labs(lhs) == rhs) {
        i64* result = malloc(3 * sizeof *result);
        result[0] = array->s1;
        result[1] = array->t1;
        result[2] = array->a;
        free(array);
        return result;
    } else {
        perror("error calculating EEA.\n");
        printf("a = %ld\nb = %ld\ns = %ld\nt = %ld\ngcd = %ld\n", a, b, array->s1, array->t1, array->a);
        free(array);
        return NULL;
    }
}

/*
Finds the multiplicative inverse of a bit pattern `num` in the finite field
GF(2^32) modulo `n`. This is implemented using the Extended Euclidean Algorithm.

Input: the starting bit pattern.
Output: the modular multiplicative inverse of the bit pattern. Returns -1
if it does not exist.
*/
i64 modular_MI(i64 num, i64 n) {
    i64* result = eea_full(n, num);
    return mod(result[1], n);
}