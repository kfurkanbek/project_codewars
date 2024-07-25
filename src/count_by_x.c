/**
 * @brief a function with two arguments that will return an array of the first n
multiples of x.
 *
 * @param x
 * @param n
 * @param result
 */
void count_by(unsigned x, unsigned n, unsigned result[n])
{
    for (unsigned i = 0; i < n; i++)
    {
        result[i] = (i + 1) * x;
    }
}
