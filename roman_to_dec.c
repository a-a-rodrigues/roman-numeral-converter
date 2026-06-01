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

validation_status_t validate_form(char* pos[], term_form_t form) {
    // Try each "form" to determine which one fits the current term pointer to by our four char pointers
        // The greatest form initially passed will correspond with distance to end of numeral: we cannot get d = get_letter_value(*pos[3]) when it is '\0'
        // Rather than returning INVALID in individual cases, we must instead call validate_form recursively until form = EMPTY (default)
    int a;
    int b;
    int c;
    int d;

    if (DEBUG) fprintf(stdout, "We are checking to see form is valid: %d", form);
    
    switch (form) {
        case ONE_LETTER:
            return POSITIVE;

        case TWO_LETTER:
            a = get_letter_value(*pos[0]);
            b = get_letter_value(*pos[1]);

            if (DEBUG) fprintf(stdout, "We are checking to see if this term is of TWO_LETTER form: %d, %d, %d\n", a, b, c);

            if (a == b) {
                if (get_letter_base(a) == QUINARY) return INVALID;
                return POSITIVE;
            } else if (get_letter_value(*pos[0]) < get_letter_value(*pos[1])) {
                if ((get_letter_base(*pos[0]) == QUINARY) || (get_letter_value(*pos[0]) < get_letter_value(*pos[1]) / 10)) return INVALID;
                return NEGATIVE;
            }             
            return POSITIVE;
        
        case THREE_LETTER:
            a = get_letter_value(*pos[0]);
            b = get_letter_value(*pos[1]);
            c = get_letter_value(*pos[2]);

            if (DEBUG) fprintf(stdout, "We are checking to see if this term is of THREE_LETTER form: %d, %d, %d\n", a, b, c);

            if (a == b) {
                if (get_letter_base(a) == QUINARY) return INVALID;
                if (b != c) return INVALID;
                return POSITIVE;
            } else if (b == c) {
                if (get_letter_base(b) == QUINARY) return INVALID;
                if (a < b) return INVALID;
                return POSITIVE;
            } 
            return INVALID;

        case FOUR_LETTER:
            a = get_letter_value(*pos[0]);
            b = get_letter_value(*pos[1]);
            c = get_letter_value(*pos[2]);
            d = get_letter_value(*pos[3]);

            if (DEBUG) fprintf(stdout, "We are checking to see if this term is of THREE_LETTER form: %d, %d, %d, %d\n", a, b, c, d);

            if (b == c && c == d) {
                if (get_letter_base(b) == QUINARY) return INVALID;
                if (a < b) return INVALID;
                return POSITIVE;
            }

            return INVALID;                

        default:
            return INVALID;
    }

}

int decimalize(char* roman) {
    char* pos[4];
    term_form_t form = EMPTY;
    
    for (int i = 0; i < 4; i++) {
        if (DEBUG) fprintf(stdout, " roman[%d]: %c\n", i, *(roman + i));

        if (*(roman + i) != '\0') {
            pos[i] = (roman + i);
            form++;
        }
        else
            *pos[i] = '\0';
    }

    validation_status_t status;

    while (form != EMPTY){
        status = validate_form(pos, form);
        form--;
    }

    if (DEBUG) fprintf(stdout, "The characters selected right now are %c | %c | %c | %c | \nValidation: %d\n", *pos[0], *pos[1], *pos[2], *pos[3], status);

    return 1;

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