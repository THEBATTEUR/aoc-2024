/*
 * NMC
 * Advent of code day 2
 */
#include <stdio.h>
#include <stdlib.h>

typedef enum OrderType OrderType;
enum OrderType {
    UNDEFINED = -1,
    DSC = 0,
    ASC = 1
};

int main(void) {
    FILE *inputFile = NULL;
    inputFile = fopen("../day02/input", "r");
    if (inputFile == NULL) {
        printf("Fatal error : cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    OrderType order = UNDEFINED;
    int16_t previous = -1, skip = 0;
    int16_t number = 0;
    u_int16_t total = 0;
    char inputChar = -1;
    while (!feof(inputFile)) {
        inputChar = fgetc(inputFile);
        if (inputChar != ' ' && inputChar != '\n') {
            number *= 10;
            number += inputChar - '0';
        } else if (!skip && number != 0) {
            if (previous != -1) {
                if (order == UNDEFINED)
                    order = previous < number;
                if ((order && previous > number) ||
                    (!order && previous < number) ||
                    (abs(previous - number) < 1 || abs(previous - number) > 3)) {
                    skip = 1;
                }
            }
            previous = number;
            number = 0;
        }
        if (inputChar == '\n' || inputChar == EOF) {
            if (!skip) {
                total++;
            }
            previous = -1;
            order = UNDEFINED;
            number = 0;
            skip = 0;
        }
    }
    printf("Total of safe: %d", total);
    fclose(inputFile);
}
