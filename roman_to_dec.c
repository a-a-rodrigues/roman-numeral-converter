#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#ifndef DEBUG
#define DEBUG 0
#endif

#define BUFFSIZE 32

#define M 1000
#define D 500
#define C 100
#define L 50
#define X 10
#define V 5
#define I 1

/**
 *  TODO: 
 *      Create performance tests
 *      Allow run from file
 *      Make variables (number, numeral, decimal) more consistent, defined
 *      Implement specific error conditions, output
 *      Implement interactive mode
 *      Fix data types for space efficiency 
 */

int decimalize(char* roman) {
    int decimal = 0;
    int mCount = 0;
    int dCount = 0;
    int cCount = 0; 
    int lCount = 0;
    int xCount = 0;
    int vCount = 0;
    int iCount = 0;
    bool hundreds_flag = false;
    bool tens_flag = false;
    bool ones_flag = false;

    for (char* cur = roman; *cur != '\0'; cur++) {
        fprintf(stdout, "%c, ", *cur);
        switch (*cur) {
            case 'M':
                if (iCount > 0 || vCount > 0 || xCount > 0 || lCount > 0 
                    || cCount > 1 || dCount > 0 || mCount == 3 || hundreds_flag)
                    return 0;
                if (cCount == 1 && mCount < 3) {
                    decimal -= C * 2;
                    hundreds_flag = true;
                }

                decimal += M;

                mCount++;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'D':
                if (iCount > 0 || vCount > 0 || xCount > 0 || lCount > 0 
                    || cCount > 1 || dCount > 0 || hundreds_flag)
                    return 0;
                if (cCount == 1) {
                    decimal -= C * 2;
                    hundreds_flag = true;
                }

                dCount++;
                decimal += D;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'C':
                if (iCount > 0 || vCount > 0 || xCount > 1 || lCount > 0 
                    || cCount == 3 || tens_flag)
                    return 0;
                if (xCount == 1 && cCount < 3) {
                    decimal -= X * 2;
                    tens_flag = true;
                }

                cCount++;
                decimal += C;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'L':
                if (iCount > 0 || vCount > 0 || xCount > 1 
                    || lCount > 0 || tens_flag)
                    return 0;
                if (xCount == 1) {
                    decimal -= X * 2;
                    tens_flag = true;
                }

                lCount++;
                decimal += L;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'X':
                if (iCount > 1 || vCount > 0 || xCount == 3 || ones_flag)
                    return 0;
                if (iCount == 1 && xCount < 3) {
                    decimal -= I * 2;
                    ones_flag = true;
                }
                
                xCount++;
                decimal += X;
                printf("Current dec: %d\n", decimal);
                break;
            case 'V':
                if (iCount > 1 || vCount > 0 || ones_flag)
                    return 0;
                if (iCount == 1) {
                    decimal -= I * 2;
                    ones_flag = true;
                }

                vCount++;
                decimal += V;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'I': 
                if (iCount == 3)
                    return 0;

                iCount++;
                decimal += I;
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