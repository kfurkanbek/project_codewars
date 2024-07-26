#include "test_project_codewars.h"
#include "../src/project_codewars.h"
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>

static void repeat_func(void func(void), unsigned int count)
{
    while (count > 0)
    {
        func();
        count--;
    }
}

static void test_reverse_words(void)
{
    CU_ASSERT_STRING_EQUAL_FATAL(reverseWords("This is an example!"),
                                 "sihT si na !elpmaxe");

    CU_ASSERT_STRING_EQUAL_FATAL(reverseWords("double  spaces"),
                                 "elbuod  secaps");
}

static void test_fake_binary(void)
{
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

static void test_find_min_max(void)
{
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

static void test_play_digits(void)
{
    CU_ASSERT_EQUAL_FATAL(digPow(89, 1), 1);
    CU_ASSERT_EQUAL_FATAL(digPow(92, 1), -1);
    CU_ASSERT_EQUAL_FATAL(digPow(695, 2), 2);
    CU_ASSERT_EQUAL_FATAL(digPow(46288, 3), 51);
}

static void test_dna_rna_random(void)
{
    size_t pos    = -1;
    size_t length = 10;
    char*  dna    = malloc((length + 1) * sizeof(char));
    char*  rna    = malloc((length + 1) * sizeof(char));
    if (dna == NULL || rna == NULL)
    {
        free(dna);
        free(rna);

        CU_FAIL_FATAL("cannot initialize random tests");
        return;
    }
    dna[length] = '\0';
    rna[length] = '\0';

    while (++pos < length)
    {
        short random = rand() % 4;

        switch (random)
        {
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
            CU_FAIL_FATAL("unexpected random value in random tests");
        }
    }

    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna(dna), rna);

    free(dna);
    free(rna);
}

static void test_dna_rna(void)
{
    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna("TTTT"), "UUUU");
    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna("GCAT"), "GCAU");
    CU_ASSERT_STRING_EQUAL_FATAL(dna_to_rna("GACCGCCGCC"), "GACCGCCGCC");

    repeat_func(test_dna_rna_random, 7);
}

static void test_count_by_x(void)
{
    size_t    length   = 5;
    unsigned* actual   = malloc(length * sizeof(unsigned));
    unsigned* expected = NULL;

    count_by(1, 5, actual);
    expected = (unsigned[]){1, 2, 3, 4, 5};

    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    count_by(3, 5, actual);
    expected = (unsigned[]){3, 6, 9, 12, 15};
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    count_by(2, 5, actual);
    expected = (unsigned[]){2, 4, 6, 8, 10};
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    count_by(50, 5, actual);
    expected = (unsigned[]){50, 100, 150, 200, 250};
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    count_by(100, 5, actual);
    expected = (unsigned[]){100, 200, 300, 400, 500};
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    free(actual);
}

static void test_will_you_make(void)
{
    CU_ASSERT_EQUAL_FATAL(zero_fuel(50, 25, 2), true);
    CU_ASSERT_EQUAL_FATAL(zero_fuel(60, 30, 3), true);
    CU_ASSERT_EQUAL_FATAL(zero_fuel(70, 25, 1), false);
    CU_ASSERT_EQUAL_FATAL(zero_fuel(100, 25, 3), false);
}

static void test_odd_even(void)
{
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0}, 1), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){1}, 1), "odd");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even(NULL, 0), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, 1, 5}, 3), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, 1, 3}, 3), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){1023, 1, 2}, 3), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, -1, -5}, 3), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, -1, -3}, 3), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){-1023, 1, -2}, 3), "even");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, 1, 2}, 3), "odd");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, 1, 4}, 3), "odd");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){1023, 1, 3}, 3), "odd");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, -1, 2}, 3), "odd");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){0, 1, -4}, 3), "odd");
    CU_ASSERT_STRING_EQUAL_FATAL(odd_or_even((int[]){-1023, -1, 3}, 3), "odd");
}

static void test_cnvrt_str_arr(void)
{
    size_t length   = 1;
    char** actual   = malloc(length * sizeof(char*));
    char** expected = NULL;

    length = 1;
    actual = realloc(actual, length * sizeof(char*));
    words_to_array("word", actual);
    expected = (char*[]){"word"};
    for (size_t i = 0; i < length; i++)
    {
        CU_ASSERT_EQUAL_FATAL(sizeof(actual[i]), sizeof(expected[i]));
        CU_ASSERT_STRING_EQUAL_FATAL(actual[i], expected[i]);
    }

    length = 2;
    actual = realloc(actual, length * sizeof(char*));
    words_to_array("Robin Singh", actual);
    expected = (char*[]){"Robin", "Singh"};
    for (size_t i = 0; i < length; i++)
    {
        CU_ASSERT_EQUAL_FATAL(sizeof(actual[i]), sizeof(expected[i]));
        CU_ASSERT_STRING_EQUAL_FATAL(actual[i], expected[i]);
    }

    length = 3;
    actual = realloc(actual, length * sizeof(char*));
    words_to_array("a b c", actual);
    expected = (char*[]){"a", "b", "c"};
    for (size_t i = 0; i < length; i++)
    {
        CU_ASSERT_EQUAL_FATAL(sizeof(actual[i]), sizeof(expected[i]));
        CU_ASSERT_STRING_EQUAL_FATAL(actual[i], expected[i]);
    }

    length = 7;
    actual = realloc(actual, length * sizeof(char*));
    words_to_array("I love arrays they are my favorite", actual);
    expected =
        (char*[]){"I", "love", "arrays", "they", "are", "my", "favorite"};
    for (size_t i = 0; i < length; i++)
    {
        CU_ASSERT_EQUAL_FATAL(sizeof(actual[i]), sizeof(expected[i]));
        CU_ASSERT_STRING_EQUAL_FATAL(actual[i], expected[i]);
    }

    free(actual);
}

static void test_rev_seq_random(void)
{
    size_t          max      = 1000;
    size_t          random   = 0;
    unsigned short* actual   = NULL;
    unsigned short* expected = NULL;

    random   = (rand() % max) + 1;
    actual   = reverse_seq(random);
    expected = malloc(random * sizeof(unsigned short));
    for (size_t i = 0; i < random; i++)
    {
        expected[i] = random - i;
    }
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    free(actual);
    free(expected);
}

static void test_rev_seq(void)
{
    unsigned short* actual   = NULL;
    unsigned short* expected = NULL;

    actual   = reverse_seq(1);
    expected = (unsigned short[]){1};
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);
    free(actual);

    actual   = reverse_seq(5);
    expected = (unsigned short[]){5, 4, 3, 2, 1};
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);
    free(actual);

    actual   = reverse_seq(0);
    expected = (unsigned short[]){0};
    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);
    free(actual);

    repeat_func(test_rev_seq_random, 7);
}

static void test_rgb_to_hex(void)
{
    char* actual   = malloc((6 + 1) * sizeof(char));
    char* expected = NULL;

    rgb(255, 255, 255, actual);
    expected = "FFFFFF";

    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    rgb(255, 255, 300, actual);
    expected = "FFFFFF";

    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    rgb(0, 0, 0, actual);
    expected = "000000";

    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    rgb(148, 0, 211, actual);
    expected = "9400D3";

    CU_ASSERT_EQUAL_FATAL(sizeof(actual), sizeof(expected));
    CU_ASSERT_STRING_EQUAL_FATAL(actual, expected);

    free(actual);
}

static void test_equal_sides(void)
{
    CU_ASSERT_EQUAL_FATAL(find_even_index((int[]){1, 2, 3, 4, 3, 2, 1}, 7), 3);

    CU_ASSERT_EQUAL_FATAL(find_even_index((int[]){1, 100, 50, -51, 1, 1}, 6),
                          1);

    CU_ASSERT_EQUAL_FATAL(find_even_index((int[]){1, 2, 3, 4, 5, 6}, 6), -1);

    CU_ASSERT_EQUAL_FATAL(
        find_even_index((int[]){20, 10, 30, 10, 10, 15, 35}, 7), 3);

    CU_ASSERT_EQUAL_FATAL(
        find_even_index((int[]){20, 10, -80, 10, 10, 15, 35}, 7), 0);

    CU_ASSERT_EQUAL_FATAL(
        find_even_index((int[]){10, -80, 10, 10, 15, 35, 20}, 7), 6);

    CU_ASSERT_EQUAL_FATAL(find_even_index((int[]){0, 0, 0, 0, 0}, 5), 0);

    CU_ASSERT_EQUAL_FATAL(
        find_even_index((int[]){-1, -2, -3, -4, -3, -2, -1}, 7), 3);
}

int main(void)
{
    // Initialize the CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS)
    {
        return CU_get_error();
    }

    // Add a suite to the registry
    CU_pSuite suite = CU_add_suite("project_codewars", NULL, NULL);
    if (suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if (CU_add_test(suite, "reverse_words", test_reverse_words) == NULL ||
        CU_add_test(suite, "fake_binary", test_fake_binary) == NULL ||
        CU_add_test(suite, "find_min_max", test_find_min_max) == NULL ||
        CU_add_test(suite, "play_digits", test_play_digits) == NULL ||
        CU_add_test(suite, "dna_rna", test_dna_rna) == NULL ||
        CU_add_test(suite, "count_by_x", test_count_by_x) == NULL ||
        CU_add_test(suite, "will_you_make", test_will_you_make) == NULL ||
        CU_add_test(suite, "odd_even", test_odd_even) == NULL ||
        CU_add_test(suite, "convert_string_arr", test_cnvrt_str_arr) == NULL ||
        CU_add_test(suite, "reversed_sequence", test_rev_seq) == NULL ||
        CU_add_test(suite, "rgb_to_hex", test_rgb_to_hex) == NULL ||
        CU_add_test(suite, "equal_sides", test_equal_sides) == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Set the output base filename
    // (CUnit will append "-Results.xml" and "-Listing.xml")
    CU_set_output_filename("report/CUnitAutomated");

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
