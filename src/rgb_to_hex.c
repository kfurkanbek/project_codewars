#include <stdio.h>
#include <stdlib.h>

/**
 * @brief A function that wraps the unsigned digit values
 * and returns a char array that contains the corresponding hex values
 *
 * @param n
 * @param hex
 * @param len
 */
static void unsigned_digit_to_char_hex(int n, char* hex, size_t len)
{
    if (n < 0)
    {
        n = 0;
    }
    else if (n > 255)
    {
        n = 255;
    }

    snprintf(hex, len, "%.2X", n);
}

/**
 * @brief A function so that passing in RGB decimal values will result in
 * a hexadecimal representation being returned.
 *
 * @param r
 * @param g
 * @param b
 * @param hex
 */
void rgb(int r, int g, int b, char hex[6 + 1])
{
    char* buff = malloc((2 + 1) * sizeof(char));
    if (buff == NULL)
    {
        hex[0] = '\0';
        return;
    }

    unsigned_digit_to_char_hex(r, buff, (2 + 1));
    hex[0] = buff[0];
    hex[1] = buff[1];

    unsigned_digit_to_char_hex(g, buff, (2 + 1));
    hex[2] = buff[0];
    hex[3] = buff[1];

    unsigned_digit_to_char_hex(b, buff, (2 + 1));
    hex[4] = buff[0];
    hex[5] = buff[1];

    hex[6] = '\0';
    free(buff);

    return;
}
