/*
* NMC
 * Advent of code day 1 but I'm doing it on 4 bc why not
 */
#include <stdio.h>
#include <stdlib.h>

int ascendantComparator(const u_int32_t *t1, const u_int32_t *t2) {
    return *t1 - *t2;
}

u_int16_t getNbLineInFile(FILE *file) {
    u_int16_t total = 0;
    while(!feof(file)) {
        if(fgetc(file) == '\n') {
            total++;
        }
    }
    rewind(file);
    return total;
}

int main(void) {
    FILE *inputFile = NULL;
    inputFile = fopen("../input", "r");
    if (inputFile == NULL) {
        printf("Fatal error : cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    const u_int16_t nbLine = getNbLineInFile(inputFile);
    u_int32_t *left, *right;
    left = malloc(nbLine * sizeof(u_int32_t));
    right = malloc(nbLine * sizeof(u_int32_t));
    if (left == NULL || right == NULL) {
        printf("Fatal error : cannot allocate.\n");
        exit(EXIT_FAILURE);
    }

    u_int8_t leftSide = 1;
    u_int16_t lineCounter = 0;
    u_int32_t number = 0;
    char inputChar = -1;
    while (!feof(inputFile)) {
        inputChar = fgetc(inputFile);
        if (inputChar != ' ' && inputChar != '\n') {
            number *= 10;
            number += inputChar - '0';
        } else if (number != 0) {
            if (leftSide) {
                left[lineCounter] = number;
                leftSide--;
            } else {
                right[lineCounter++] = number;
                leftSide++;
            }
            number = 0;
        }
    }

    qsort(left, lineCounter, sizeof(u_int32_t), ascendantComparator);
    qsort(right, lineCounter, sizeof(u_int32_t), ascendantComparator);
    u_int32_t total = 0;
    for (u_int16_t i = 0; i < lineCounter; i++) {
        total += abs(left[i] - right[i]);
    }
    printf("Distance: %u\n", total);
    free(left);
    free(right);
    fclose(inputFile);
    return EXIT_SUCCESS;
}
