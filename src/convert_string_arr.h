#include <stdlib.h>

/*

Write a function to split a string and convert it into an array of words.
Examples (Input ==> Output):

"Robin Singh" ==> ["Robin", "Singh"]

"I love arrays they are my favorite" ==> ["I", "love", "arrays", "they", "are",
"my", "favorite"]

Words will be separated by exactly one space, without leading or trailing
spaces.

There will only be letters and spaces in the input string.

*/

size_t count_words(const char* words);
void words_to_array(const char* words, char* words_array[]);