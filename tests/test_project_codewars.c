#include "test_project_codewars.h"
#include "../src/project_codewars.h"
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>

static void repeat_func(void func(), unsigned int count) {
    while (count > 0) {
        func();
        count--;
    }
}

static void test_reverse_words(void) {
    CU_ASSERT_STRING_EQUAL_FATAL(reverseWords("This is an example!"),
                                 "sihT si na !elpmaxe");

    CU_ASSERT_STRING_EQUAL_FATAL(reverseWords("double  spaces"),
                                 "elbuod  secaps");
}

static void test_fake_binary(void) {
    char* result = malloc(100 * sizeof(char));

    fakeBin("45385593107843568", result);
    CU_ASSERT_STRING_EQUAL_FATAL(result, "01011110001100111");

    fakeBin("509321967506747", result);
    CU_ASSERT_STRING_EQUAL_FATAL(result, "101000111101101");

    fakeBin("366058562030849490134388085", result);
    CU_ASSERT_STRING_EQUAL_FATAL(result, "011011110000101010000011011");

    fakeBin("15889923", result);
    CU_ASSERT_STRING_EQUAL_FATAL(result, "01111100");

    fakeBin("800857237867", result);
    CU_ASSERT_STRING_EQUAL_FATAL(result, "100111001111");

    free(result);
}

static void test_find_min_max(void) {
    CU_ASSERT_EQUAL_FATAL(max((int[8]){4, 6, 2, 1, 9, 63, -134, 566}, 8), 566);
    CU_ASSERT_EQUAL_FATAL(min((int[8]){4, 6, 2, 1, 9, 63, -134, 566}, 8), -134);

    CU_ASSERT_EQUAL_FATAL(max((int[7]){-52, 56, 30, 29, -54, 0, -110}, 7), 56);
    CU_ASSERT_EQUAL_FATAL(min((int[7]){-52, 56, 30, 29, -54, 0, -110}, 7),
                          -110);

    CU_ASSERT_EQUAL_FATAL(max((int[5]){42, 54, 65, 87, 0}, 5), 87);
    CU_ASSERT_EQUAL_FATAL(min((int[5]){42, 54, 65, 87, 0}, 5), 0);

    CU_ASSERT_EQUAL_FATAL(max((int[1]){5}, 1), 5);
    CU_ASSERT_EQUAL_FATAL(min((int[1]){5}, 1), 5);
}

static void test_play_digits(void) {
    CU_ASSERT_EQUAL_FATAL(digPow(89, 1), 1);
    CU_ASSERT_EQUAL_FATAL(digPow(92, 1), -1);
    CU_ASSERT_EQUAL_FATAL(digPow(695, 2), 2);
    CU_ASSERT_EQUAL_FATAL(digPow(46288, 3), 51);
}

static void test_dna_to_rna_random(void) {
    size_t pos = -1;
    size_t length = 10;
    char* dna = malloc((length + 1) * sizeof(char));
    char* rna = malloc((length + 1) * sizeof(char));
    if (dna == NULL || rna == NULL) {
        CU_FAIL_FATAL("cannot initialize random tests");
    }
    dna[length] = '\0';
    rna[length] = '\0';

    while (++pos < length) {
        short random = rand() % 4;

        switch (random) {
        case 0:
            dna[pos] = 'G';
            rna[pos] = 'G';
            break;
        case 1:
            dna[pos] = 'C';
            rna[pos] = 'C';
            break;
        case 2:
            dna[pos] = 'A';
            rna[pos] = 'A';
            break;
        case 3:
            dna[pos] = 'T';
            rna[pos] = 'U';
            break;
        default:
            free(dna);
            free(rna);
            CU_FAIL_FATAL("unexpected random value in random tests");
        }
    }

    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna(dna), rna);

    free(dna);
    free(rna);
}

static void test_dna_to_rna(void) {
    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna("TTTT"), "UUUU");
    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna("GCAT"), "GCAU");
    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna("GACCGCCGCC"), "GACCGCCGCC");

    repeat_func(test_dna_to_rna_random, 7);
}

int main() {
    // Initialize the CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add a suite to the registry
    CU_pSuite suite = CU_add_suite("project_codewars", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if (CU_add_test(suite, "test_reverse_words", test_reverse_words) == NULL ||
        CU_add_test(suite, "test_fake_binary", test_fake_binary) == NULL ||
        CU_add_test(suite, "test_find_min_max", test_find_min_max) == NULL ||
        CU_add_test(suite, "test_play_digits", test_play_digits) == NULL ||
        CU_add_test(suite, "test_dna_to_rna", test_dna_to_rna) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Run automated tests and output results to files
    CU_automated_run_tests();
    CU_list_tests_to_file();

    // Clean up registry and return
    CU_cleanup_registry();
    return CU_get_error();

    return 0;
}