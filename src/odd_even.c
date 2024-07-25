#include <stddef.h>

/**
 * @brief Given a list of integers,
determines whether the sum of its elements is odd or even.
 *
 * @param v
 * @param sz
 * @return const char*
 */
const char* odd_or_even(const int* v, size_t sz)
{
    int sum = 0;
    for (size_t i = 0; i < sz; i++)
    {
        sum += v[i];
    }

    return (sum % 2) ? "odd" : "even";
}
