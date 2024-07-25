#include <stdlib.h>

/**
 * @brief a function that returns an array of integers from n to 1 (n > 0)
 *
 * @param num
 * @return unsigned*
 */
unsigned short* reverse_seq(unsigned short num) {
    unsigned short* seq = malloc(1 * sizeof(unsigned short));
    if (seq == NULL) {
        return NULL;
    }
    seq[0] = 0;

    if (num == 0) {
        return seq;
    }

    seq = malloc(num * sizeof(unsigned short));
    if (seq == NULL) {
        return NULL;
    }

    for (unsigned short i = 0; i < num; i++) {
        seq[i] = num - i;
    }

    return seq;
}