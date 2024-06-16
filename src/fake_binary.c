#include <stdlib.h>

/**
 * @brief A function that when given a string of digits, should replace any
digit below 5 with '0' and any digit 5 and above with '1'. Returns the resulting
string.

 *
 * @param digits
 * @param binary
 */
void fakeBin(const char* digits, char* binary) {
    size_t digits_l = -1;
    while (digits[++digits_l] != '\0') {
    }
    binary[digits_l] = '\0';

    for (size_t i = 0; i < digits_l; i++) {

        if (digits[i] < '0' || '9' < digits[i]) {
            binary[i] = digits[i];
            continue;
        }

        if (digits[i] < '5') {
            binary[i] = '0';
        } else {
            binary[i] = '1';
        }
    }

    return;
}