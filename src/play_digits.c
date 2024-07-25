#include <stdio.h>
#include <stdlib.h>

/**
 * @brief A function that returns n to the power of p
 *
 * @param n
 * @param p
 * @return int
 */
static int _power(int n, int p)
{
    if (p < 0)
    {
        return 0;
    }

    int result = 1;
    while (p > 0)
    {
        result *= n;
        p--;
    }

    return result;
}

/**
 * @brief Writing the consecutive digits of n as a, b, c, d ...,
 is there an integer k such that : (ap+bp+1+cp+2+dp+3+...)
 n ∗ k (a^p + b^{p + 1} + c^{p + 2}+ d^{p + 3} + ...) = n * k
 (ap+bp+1+cp+2+dp+3+...) = n∗k

 If it is the case we will return k, if not return -1.

 *
 * @param n
 * @param p
 * @return int
 */
int digPow(int n, int p)
{

    char* buff = malloc(100 * sizeof(char));
    if (buff == NULL)
    {
        return -1;
    }
    buff[99] = '\0';

    int ret = snprintf(buff, 100, "%d", n);
    if (ret < 0)
    {
        free(buff);
        return -1;
    }

    int   sum = 0;
    short i   = -1;
    while (buff[++i] != '\0')
    {
        if (buff[i] == '-')
        {
            continue;
        }

        int digit  = buff[i] - '0';
        sum       += _power(digit, p);
        p++;
    }
    free(buff);

    if (sum % n != 0)
    {
        return -1;
    }

    return (sum / n);
}
