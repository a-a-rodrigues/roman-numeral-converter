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
 */

typedef enum {
    ONE,
    TWO,
    THREE,
    FOUR,
} consecutive_t;

int number_to_decimal(char n){
    switch(n) {
        case 'M': return 1000;
        case 'D': return 500;
        case 'C': return 100;
        case 'L': return 50;
        case 'X': return 10;
        case 'V': return 5;
        case 'I': return 1;
        default: return -4000;
    }
}

int decimal_to_numeral(char* numeral) {
    if (strlen(numeral) > 16) {
        fprintf(stdout, "Your input is too long to be a Roman numeral! The max length is 15 characters!");
        return 0;
    }
    
    int value = 0;
    int lowest = 3889, highest = 0;
    bool increasing = false;
    consecutive_t consecutive = ONE;

    for (char *cur = numeral, *next = (numeral + 1); *cur != '\0'; cur++, next++) {        
        // Avoid repeat calls to number_to_decimal by calling it from the start
        int number = number_to_decimal(*cur);
        int next_number = number_to_decimal(*next);

        if (number < 0) return 0;

        // Checks lowest/highest denominations thus far
        if (number < lowest) lowest = number;
        if (number > highest) highest = number;

        // Set flag indicating if values are going from less -> greater
            // If this this happens while numeral is already increasing, imples "takeaway" of > 1 numeral
            // Otherwise, set increasing to true for next pass, or not increasing, maybe consecutive
        if (number < next_number) {
           if (increasing) return 0;
           increasing = true;
        } else if (number == next_number) {
            consecutive++;
            increasing = false; 
        } else {
            consecutive = ONE;
            increasing = false; 
        }

        // Check if four (or more) consecutive numerals are present
        if (consecutive == FOUR)
            return 0;

        // Check conditions which invalidate numeral by way of invalid D, L, V:
            // D, L, V cannot appear consecutively, nor be "taken away" by coming before a greater numeral
        if (number % 3 == 2) {
            if (increasing || consecutive > ONE) return 0;
        }

        // To wit, if decreasing (e.g., not increasing and not the same as the next) illegally, invalid number
        if (!increasing && consecutive == ONE && next_number >= lowest)
            return 0;
        
        // Finalize logic that will add/subtract as befitting conditions
        if (increasing)
            value -= number_to_decimal(*cur); 
        else
            value += number_to_decimal(*cur);
        
        if (DEBUG) printf("Current: %c\tValue: %d\tNext: %c\t\tNext Val: %d\t"
            "Lowest Number: %d\tHighest Number: %d\tIncreasing: %d\t Consec: %d\n", *cur, number, *next, number_to_decimal(*next), 
            lowest, highest, increasing, consecutive);

        if (DEBUG) printf("Currently, our Roman numeral is calculated at a value of: %d\n\n", value);
    }

    return value;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stdout, "Usage: ./num_to_dec <1-3888>\n");
        return EXIT_FAILURE;
    }

    char* numeral = argv[1];
    int value = decimal_to_numeral(numeral);

    if (value)
        fprintf(stdout, "The Roman numeral %s is %d in decimal.\n", numeral, value);
    else
        fprintf(stdout, "%s is not a valid Roman numeral.\n", numeral);

    return EXIT_SUCCESS;
}