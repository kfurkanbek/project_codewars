#include "convert_string_arr.h"

/**
 * @brief Counts the number of words
 this function will be used to allocate the right amount of memory so it
 has to be correct !
 *
 * @param words
 * @return size_t
 */
size_t count_words(const char* words)
{
    size_t count   = 0;
    size_t i       = -1;
    short  is_word = 1;

    while (words[++i] != '\0')
    {
        if (words[i] == ' ')
        {
            is_word = 1;
            continue;
        }

        if (is_word == 0)
        {
            continue;
        }

        count++;
        is_word = 0;
    }

    return count;
}

/**
 * @brief A function that splits a string and convert it into an array of words.
 allocate the words on the heap, they will be freed write them to the
 pre-allocated words_array
 *
 * @param words
 * @param words_array
 */
void words_to_array(const char* words, char* words_array[])
{
    size_t length   = 0;
    size_t word_n   = 0;
    size_t letter_n = 0;
    size_t i        = -1;

    while (words[++i] != '\0')
    {
    }
    length = i;
    i      = -1;

    char* buffer = malloc((length + 1) * sizeof(char));
    if (buffer == NULL)
    {
        return;
    }
    buffer[length] = '\0';

    while (words[++i] != '\0')
    {
        if (words[i] != ' ')
        {
            buffer[letter_n] = words[i];
            letter_n++;
            continue;
        }

        if (letter_n == 0)
        {
            continue;
        }

        words_array[word_n] = malloc((letter_n + 1) * sizeof(char));
        if (words_array[word_n] == NULL)
        {
            for (size_t k = 0; k < word_n; k++)
            {
                free(words_array[k]);
            }

            free(buffer);
            return;
        }

        for (size_t j = 0; j < letter_n; j++)
        {
            words_array[word_n][j] = buffer[j];
        }
        words_array[word_n][letter_n] = '\0';

        word_n++;
        letter_n = 0;
    }

    if (letter_n > 0)
    {
        words_array[word_n] = malloc((letter_n + 1) * sizeof(char));
        if (words_array[word_n] == NULL)
        {
            for (size_t k = 0; k < word_n; k++)
            {
                free(words_array[k]);
            }

            free(buffer);
            return;
        }

        for (size_t j = 0; j < letter_n; j++)
        {
            words_array[word_n][j] = buffer[j];
        }
        words_array[word_n][letter_n] = '\0';

        word_n++;
    }

    size_t word_n_calc = count_words(words);
    if (word_n != word_n_calc)
    {
        for (size_t j = 0; j < word_n; j++)
        {
            free(words_array[j]);
        }
    }

    free(buffer);
    return;
}
