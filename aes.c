#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sub_bytes(__uint32_t* word);
void shift_rows(char *matrix);
void mix_columns(char *matrix);
void add_round_key(char *matrix);
__uint32_t group(__uint32_t word);
__uint32_t *expand_key(__uint32_t key[4]);

char *aes_encrypt128(char *message) {
    // sub_bytes();
    // shift_rows();
    // mix_columns();
    // add_round_key();
    int statearray[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            statearray[j][i] = 4 * i + j;
        }
    }

    __uint32_t key[4] = {0x01010101,0x01010101,0x01010101,0x01010101};
    __uint32_t* expanded_key = expand_key(key);
}


__uint32_t *expand_key(__uint32_t key[4]) {
    __uint32_t *key_schedule = malloc(44 * sizeof *key_schedule);
    for (int i = 4; i < 44; i += 4) {
        key_schedule[i] = group(key_schedule[i - 1]) ^ key_schedule[i - 4];
        key_schedule[i + 1] = key_schedule[i] ^ key_schedule[i - 3];  
        key_schedule[i + 2] = key_schedule[i + 1] ^ key_schedule[i - 2];  
        key_schedule[i + 3] = key_schedule[i + 2] ^ key_schedule[i - 1];  
    }
}
__uint32_t group(__uint32_t word) {
    word = (word << 8) | (word >> (32 - 8));
}


void sub_bytes(__uint32_t* word) {
    __uint8_t lookup_table[16][16];
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            lookup_table[i][j] = (i << 4) | j;
        }
    }
}
