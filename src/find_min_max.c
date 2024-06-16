#include <limits.h>

/**
 * @brief A function that receives a list of integers as input, and returns
the lowest number in that list, respectively.
 *
 * @param array
 * @param arrayLength
 * @return int
 */
int min(int* array, int arrayLength) {

    int result = INT_MAX;
    for (int i = 0; i < arrayLength; i++) {

        if (result <= array[i]) {
            continue;
        }

        result = array[i];
    }

    return result;
}

/**
 * @brief A function that receives a list of integers as input, and returns
the largest number in that list, respectively.
 *
 * @param array
 * @param arrayLength
 * @return int
 */
int max(int* array, int arrayLength) {

    int result = INT_MIN;
    for (int i = 0; i < arrayLength; i++) {

        if (result >= array[i]) {
            continue;
        }

        result = array[i];
    }

    return result;
}