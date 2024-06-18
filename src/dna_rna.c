#include <stdlib.h>

/**
 * @brief Create a function which translates a given DNA string into RNA.
 For example:
 "GCAT"  =>  "GCAU"
 *
 * @param dna
 * @return char*
 */
char* dna_to_rna(const char* dna) {
    size_t dna_l = -1;
    while (dna[++dna_l] != '\0') {
    }

    char* rna = malloc((dna_l + 1) * sizeof(char));
    if (rna == NULL) {
        return NULL;
    }
    rna[dna_l] = '\0';

    dna_l = -1;
    while (dna[++dna_l] != '\0') {
        if (dna[dna_l] == 'T') {
            rna[dna_l] = 'U';
            continue;
        }

        rna[dna_l] = dna[dna_l];
    }

    return rna;
}