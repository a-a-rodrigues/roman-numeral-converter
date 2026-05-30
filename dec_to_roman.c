#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#ifndef DEBUG
#define DEBUG 0
#endif


/**
 *  TODO: Create reverse conversion algorithm
 *      Create performance tests
 *      Allow run from file
 *      Make variables (number, numeral, decimal) more consistent, defined
 *      Implement specific error conditions, output
 *      Implement interactive mode
 *      Fix data types for space efficiency
 */

// There HAS to be a better way to do this
/*char* numerals[][] = {
    I, X, C, M
    II, XX, CC, MM
    III, XXX, CCC, MMM
    IV, XL, CD
    V, L, D
    VI, LX, DC
    VII, LXX, DCC
    VIII, LXXX, DCCC
    IX, XC, CM
}*/

void romanize(long decimal, char* roman) {
    int power = 0;
    int digit = decimal % 10;
    char* term = digit_to_roman(digit, power++);

    strcpy(roman, term);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stdout, "Usage: ./num_to_dec <1-3888>\n");
        return EXIT_FAILURE;
    }

    char *decimal_str = argv[1];
    char *endptr;
    long decimal;
    decimal = strtol(decimal_str, &endptr, 10);

    if (*endptr != '\0' || decimal_str == endptr) {
        fprintf(stdout, "Usage: ./num_to_dec <1-3888>!");
        return EXIT_FAILURE;
    }
    
    char* roman = (char *)malloc(16);
    romanize(decimal, roman);
    printf("Your number as a Roman numeral is %s\n.", roman); 

    free(roman);
    return EXIT_SUCCESS;
}