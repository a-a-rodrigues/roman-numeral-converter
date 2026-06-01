#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

#define HUNDREDS_FLAG 0x01 // 00000001
#define TENS_FLAG 0x02 // 00000010
#define ONES_FLAG 0x04 // 00000100

/**
 *  TODO: 
 *      Create performance tests (probably in a separate file)
 *      Allow run from file
 *      Make variables (number, numeral, decimal) more consistent, defined
 *      Implement specific error conditions, output
 *      Implement interactive mode
 */

int decimalize(char* roman) {
    uint16_t decimal = 0;
    uint8_t flags = 0;
    uint8_t mCount = 0;
    uint8_t dCount = 0;
    uint8_t cCount = 0; 
    uint8_t lCount = 0;
    uint8_t xCount = 0;
    uint8_t vCount = 0;
    uint8_t iCount = 0;

    for (char* cur = roman; *cur != '\0'; cur++) {
        fprintf(stdout, "%c, ", *cur);
        switch (*cur) {
            case 'M':
                if (iCount > 0 || vCount > 0 || xCount > 0 || lCount > 0 
                    || cCount > 1 || dCount > 0 || (mCount == 3 && cCount != 1) 
                    || flags & HUNDREDS_FLAG)
                    return 0;
                if (cCount == 1 && mCount <= 3) {
                    decimal -= C * 2;
                    flags |= HUNDREDS_FLAG;
                }

                decimal += M;

                mCount++;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'D':
                if (iCount > 0 || vCount > 0 || xCount > 0 || lCount > 0 
                    || cCount > 1 || dCount > 0 || flags & HUNDREDS_FLAG)
                    return 0;
                if (cCount == 1) {
                    decimal -= C * 2;
                    flags |= HUNDREDS_FLAG;
                }

                dCount++;
                decimal += D;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'C':
                if (iCount > 0 || vCount > 0 || xCount > 1 || lCount > 0 
                    || (cCount == 3 && xCount != 1) || flags & TENS_FLAG)
                    return 0;
                if (xCount == 1 && cCount <= 3) {
                    decimal -= X * 2;
                    flags |= TENS_FLAG;
                }

                cCount++;
                decimal += C;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'L':
                if (iCount > 0 || vCount > 0 || xCount > 1 
                    || lCount > 0 || flags & TENS_FLAG)
                    return 0;
                if (xCount == 1) {
                    decimal -= X * 2;
                    flags |= TENS_FLAG;
                }

                lCount++;
                decimal += L;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'X':
                if (iCount > 1 || vCount > 0 || (xCount == 3 && iCount != 1) || 
                    flags & ONES_FLAG)
                    return 0;
                if (iCount == 1 && xCount <= 3) {
                    decimal -= I * 2;
                    flags |= ONES_FLAG;
                }
                
                xCount++;
                decimal += X;
                if (DEBUG) printf("Current dec: %d\n", decimal);
                break;
            case 'V':
                if (iCount > 1 || vCount > 0 || flags & ONES_FLAG)
                    return 0;
                if (iCount == 1) {
                    decimal -= I * 2;
                    flags |= ONES_FLAG;
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

void test_correctness() {
    
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