#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#ifndef DEBUG
#define DEBUG 0
#endif

#define BUFFSIZE 32

/**
 *  TODO: Create reverse conversion algorithm
 *      Create performance tests
 *      Allow run from file
 */

typedef enum {
    QUINARY,
    DECIMAL,
} base_type_t;

typedef enum {
    EMPTY,
    ONE_LETTER,
    TWO_LETTER,
    THREE_LETTER,
    FOUR_LETTER,
} term_form_t;

typedef enum {
    NEGATIVE,
    POSITIVE,
    INVALID,
} validation_status_t;

int get_letter_value(char letter) {
    switch (letter) {
        case 'M': return 1000;
        case 'D': return 500;
        case 'C': return 100;
        case 'L': return 50;
        case 'X': return 10;
        case 'V': return 5;
        case 'I': return 1;
        default: return 0;
    }
}

base_type_t get_letter_base(char letter) {
    if (get_letter_value(letter) % 3 == 2) return QUINARY;
    return DECIMAL;
}

int decimalize(char* roman) {
    int decimal = 0;
    int mCount = 0;
    int dCount = 0;
    int cCount = 0; 
    int lCount = 0;
    int xCount = 0;
    int vCount = 0;
    int iCount = 0;

    for (char* cur = roman; *cur != '\0'; cur++) {
        fprintf(stdout, "%c, ", *cur);
        switch (*cur) {
            case 'M':
                if (iCount > 0 || vCount > 0 || xCount > 0 || lCount > 0 
                    || cCount > 1 || dCount > 0 || mCount == 3)
                    return 0;
                if (cCount == 1 && mCount < 3)
                    decimal -= 2 * get_letter_value('C');

                mCount++;
                decimal += get_letter_value('M');
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'D':
                if (iCount > 0 || vCount > 0 || xCount > 0 || lCount > 0 
                    || cCount > 1 || dCount > 0)
                    return 0;
                if (cCount == 1)
                    decimal -= 2 * get_letter_value('C');

                dCount++;
                decimal += get_letter_value('D');
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'C':
                if (iCount > 0 || vCount > 0 || xCount > 1 || lCount > 0 || cCount == 3)
                    return 0;
                if (xCount == 1 && cCount < 3)
                    decimal -= 2 * get_letter_value('X');

                cCount++;
                decimal += get_letter_value('C');
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'L':
                if (iCount > 0 || vCount > 0 || xCount > 1 || lCount > 0)
                    return 0;
                if (xCount == 1)
                    decimal -= 2 * get_letter_value('X');

                lCount++;
                decimal += get_letter_value('L');
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'X':
                if (iCount > 1 || vCount > 0 || xCount == 3)
                    return 0;
                if (iCount == 1 && xCount < 3)
                    decimal -= 2 * get_letter_value('I');
                
                xCount++;
                decimal += get_letter_value('X');
                printf("Current dec: %d\n", decimal);
                break;
            case 'V':
                if (iCount > 1 || vCount > 0)
                    return 0;
                if (iCount == 1)
                    decimal -= 2 * get_letter_value('I');

                vCount++;
                decimal += get_letter_value('V');
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'I': 
                if (iCount == 3)
                    return 0;

                iCount++;
                decimal += get_letter_value('I');
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            default:
                return 0;
        }
    }
    return decimal;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stdout, "Usage: ./num_to_dec <I-MMMDCCCLXXXVIII>\n");
        return EXIT_FAILURE;
    }

    char* roman = argv[1];
    int decimal = decimalize(roman);

    if (decimal)
        fprintf(stdout, "The Roman numeral %s is %d in decimal.\n", roman, decimal);
    else
        fprintf(stdout, "%s is not a valid Roman numeral.\n", roman);

    return EXIT_SUCCESS;
}