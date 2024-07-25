#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#define CU_BUFFER_SIZE 1024

/**
 * @brief CU_ASSERT_STRING_EQUAL_VERBOSE
 *
 */
#define CU_ASSERT_STRING_EQUAL_V(actual, expected)                             \
    {                                                                          \
        CU_VERBOSE(actual, expected);                                          \
        CU_ASSERT_STRING_EQUAL(actual, expected);                              \
    }

/**
 * @brief CU_ASSERT_STRING_EQUAL_FATAL_VERBOSE
 *
 */
#define CU_ASSERT_STRING_EQUAL_FATAL_V(actual, expected)                       \
    {                                                                          \
        CU_VERBOSE(actual, expected);                                          \
        CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);                        \
    }

/**
 * @brief CU_VERBOSE
 *
 */
#define CU_VERBOSE(actual, expected)                                           \
    {                                                                          \
        char* buffer = malloc(CU_BUFFER_SIZE * sizeof(char));                  \
        snprintf(buffer,                                                       \
                 CU_BUFFER_SIZE,                                               \
                 "CU_VERBOSE(%s (%s), %s)",                                    \
                 "" #actual "",                                                \
                 actual,                                                       \
                 "" #expected "");                                             \
        printf("\n%s\n", buffer);                                              \
        free(buffer);                                                          \
    }
