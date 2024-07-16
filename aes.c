
void sub_bytes(char *matrix);
void shift_rows(char *matrix);
void mix_columns(char *matrix);
void add_round_key(char *matrix);

char *aes_encrypt128(char *message) {
    sub_bytes();
    shift_rows();
    mix_columns();
    add_round_key();

}