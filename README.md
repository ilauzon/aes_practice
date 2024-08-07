This is a short exercise for me to familiarize myself with the AES Encryption algorithm.

# Explanation
The Advanced Encryption Standard (AES) algorithm uses a block cipher with three options for key lengths: 128, 192, and 256 bits.

Each key length option requires increasing rounds of encryption:

| Key Length | Rounds |
| ---------- | ------ |
| 128 bits   | 10     |
| 192 bits   | 12     |
| 256 bits   | 14     |

Each round includes the following steps:
- single-byte based substitution
- row-wise permutation
- column-wise mixing
- addition of the round key

Bytes in the input block are arranges in a 4x4 matrix in **column-major** order.

Other notes:
- a "word" is considered to be four bytes.
- All operations are byte-level; no bit-level access is required.

AES is an encryption algorithm designed with the wide-trail strategy, meaning that there is a wide dispersal of probabilities for any particular bit.

## Expansion of the Encryption Key
In the case of a 128-bit key, it is arranged into an array of 4 x 4 bytes in column-major order. The key is transformed into a **key schedule** of 44 words, or 1,408 bits.
- the first 4 words are used for adding to the input state of the array.
- the next 40 words are used for the 10 rounds of processing.


