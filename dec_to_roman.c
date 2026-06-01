#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#ifdef _WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

#define BUFFLENGTH 32

/**
 *  TODO: 
 *      Create performance tests
 *      Allow run from file
 *      Make variables (number, numeral, decimal) more consistent, defined
 *      Implement specific error conditions, output
 *      Implement interactive mode
 *      Fix data types for space efficiency
 */

static char *numerals[9][4] = {
    {"I", "X", "C", "M"},
    {"II", "XX", "CC", "MM"},
    {"III", "XXX", "CCC", "MMM"},
    {"IV", "XL", "CD"},
    {"V", "L", "D"},
    {"VI", "LX", "DC"},
    {"VII", "LXX", "DCC"},
    {"VIII", "LXXX", "DCCC"},
    {"IX", "XC", "CM"}
};

char* digit_to_roman(int digit, short power) {
    return numerals[digit-1][power];
}

bool romanize(char* roman, int decimal) {
    if (decimal < 0 || decimal > 3999) return false;
    
    for (short power = 0; decimal != 0; power++, decimal /= 10) {
        int digit = decimal % 10;
        if (digit != 0) {
            char* term = digit_to_roman(digit, power);

            if (DEBUG) fprintf(stdout, "Digit: %d\tPower: %hd\tTerm: %s\n", digit, power, term);

            size_t roman_len = strlen(roman);
            size_t term_len = strlen(term);

            memmove(roman + term_len, roman, roman_len + 1);
            memcpy(roman, term, term_len);
            
            if (DEBUG) fprintf(stdout, "Roman: %s\tTerm: %s\n", roman, term);
        }
    }

    return true;
}

void test_correctness (void) {
    FILE *dp;

    dp = fopen("numbers.txt", "w+");
    for (int i = 1; i < 4000; i++) {
        fprintf(dp, "%d\n", i);
    }
    fclose(dp);

    FILE *dst = fopen("romans.txt", "w");
    FILE *file = fopen("numbers.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int num;

    while (fscanf(file, "%d", &num) == 1) {
        char roman[BUFFLENGTH] = {0};
        romanize(roman, num); 
        fprintf(dst, "%s\n", roman);
    }
    
    fclose(file);
    fclose(dst);

}

int main (int argc, char** argv) {
    if (argc != 2) {
        fprintf(stdout, "Usage: ./dec_to_num <1-3999>\n");
        return EXIT_FAILURE;
    }

    if (DEBUG) test_correctness();

    char* endptr;
    int decimal = strtol(argv[1], &endptr, 10);
    if (DEBUG) fprintf(stdout, "Number input: %d\n", decimal);

    char roman[BUFFLENGTH] = {0};

    if (romanize(roman, decimal))
        fprintf(stdout, "Your number as a Roman numeral is: %s\n", roman); 
    else 
        fprintf(stdout, "Input decimal number is outisde the range of Roman numerals (1-3888)!\n");

    return EXIT_SUCCESS;
}
