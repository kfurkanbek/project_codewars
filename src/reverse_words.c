#include <stdlib.h>

/**
 * @brief A function that accepts a string parameter, and reverses
each word in the string. All spaces in the string should be retained.
 *
 * @param text
 * @return char*
 */
char* reverseWords(const char* text) {

    char split = ' ';
    size_t text_l = -1;
    while (text[++text_l] != '\0') {
    }

    char* rev = malloc((text_l + 1) * sizeof(char));
    if (rev == NULL) {
        return NULL;
    }
    rev[text_l] = '\0';

    char* buff = malloc((text_l + 1) * sizeof(char));
    if (buff == NULL) {
        return NULL;
    }
    buff[text_l] = '\0';

    size_t buff_l = 0;
    for (size_t i = 0; i < text_l; i++) {
        if (text[i] != split) {
            buff[buff_l] = text[i];
            buff_l++;
            continue;
        }

        rev[i] = text[i];
        for (size_t j = 0; j < buff_l; j++) {
            rev[i - buff_l + j] = buff[buff_l - j - 1];
        }
        buff_l = 0;
    }

    if (buff_l > 0) {
        for (size_t j = 0; j < buff_l; j++) {
            rev[text_l - buff_l + j] = buff[buff_l - j - 1];
        }
    }

    free(buff);
    return rev;
}