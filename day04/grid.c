//
// Created by nicom on 18/11/2021.
//

#include "grid.h"
#include <stdio.h>
#include <stdlib.h>

Grid load_from_file(int size, char * fileName) {
    FILE *inputFile = NULL;
    inputFile = fopen(fileName, "r");
    if (inputFile == NULL) {
        printf("Fatal error : cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    int* tableau = NULL;
    tableau = malloc(size*size*sizeof(int));
    if (tableau == NULL) {
        fprintf(stderr, "Fuck.\n");
        exit(EXIT_FAILURE);
    }
    char inputChar = -1;
    for (int i = 0; i < (size*size); ++i) {
        inputChar = fgetc(inputFile);
        if (inputChar == '\n')
            inputChar = fgetc(inputFile);
        if (inputChar == EOF)
            break;
        tableau[i] = inputChar;
    }

    fclose(inputFile);
    Grid grid = {size, tableau};
    return grid;
}

void deconstruct_grid(const Grid* grid) {
    free(grid->list);
}

void print_grid(const Grid* grid) {
    for (int i = 0; i < (grid->size*grid->size); ++i) {
        printf("%c", grid->list[i]);
        if((i+1) % grid->size == 0)
            printf("\n");
    }
}

PointStatus getValue(const Grid* grid, int r, int c) {
    int posX = 0, posY = 0;
    for (int i = 0; i < (grid->size*grid->size); ++i) {
        if(posX == c && posY == r) {
            return grid->list[i];
        }
        ++posX;
        if((i+1) % grid->size == 0) {
            posX = 0;
            ++posY;
        }
    }
    return EMPTY;
}

