/**
 * @brief A function that takes that array and find an index N where the sum of
 * the integers to the left of N is equal to the sum of the integers to the
 * right of N.
 *
 * @param values
 * @param length
 * @return int
 */
int find_even_index(const int* values, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += values[i];
    }

    int half_sum = 0;
    for (int i = 0; i < length; i++) {
        if ((sum - values[i] - half_sum) == half_sum) {
            return i;
        }

        half_sum += values[i];
    }

    return -1;
}