/*
 * NMC
 * Advent of code day 4
 */
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

#define GRID_SIZE 140

typedef enum Direction Direction;
enum Direction {
    DIAG_UP_RIGHT = 1,
    DIAG_UP_LEFT = 2,
    DIAG_DOWN_RIGHT = 3,
    DIAG_DOWN_LEFT = 4,
    UP = 5,
    DOWN = 6,
    RIGHT = 7,
    LEFT = 8
};

static const char SEQUENCE[5] = "XMAS";

u_int8_t isXmas(Grid* grid, u_int8_t r, u_int8_t c, Direction direction, u_int8_t nextLetter, u_int8_t step) {
    if ((nextLetter == 3 && step) || (nextLetter == 0 && !step))
        return getValue(grid, r, c) == SEQUENCE[nextLetter];
    switch (direction) {
        case DIAG_UP_RIGHT:
            if (r != 0 && c != GRID_SIZE-1)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r-1, c+1, DIAG_UP_RIGHT, nextLetter+step, step) : 0;
            break;
        case DIAG_UP_LEFT:
            if (r != 0 && c != 0)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r-1, c-1, DIAG_UP_LEFT, nextLetter+step, step) : 0;
            break;
        case DIAG_DOWN_RIGHT:
            if (r != GRID_SIZE-1 && c != GRID_SIZE-1)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r+1, c+1, DIAG_DOWN_RIGHT, nextLetter+step, step) : 0;
            break;
        case DIAG_DOWN_LEFT:
            if (r != GRID_SIZE-1 && c != 0)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r+1, c-1, DIAG_DOWN_LEFT, nextLetter+step, step) : 0;
            break;
        case UP:
            if (r != 0)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r-1, c, UP, nextLetter+step, step) : 0;
            break;
        case DOWN:
            if (r != GRID_SIZE-1)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r+1, c, DOWN, nextLetter+step, step) : 0;
            break;
        case RIGHT:
            if (c != GRID_SIZE-1)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r, c+1, RIGHT, nextLetter+step, step) : 0;
            break;
        case LEFT:
            if (c != 0)
                return getValue(grid, r, c) == SEQUENCE[nextLetter] ? isXmas(grid, r, c-1, LEFT, nextLetter+step, step) : 0;
            break;
        default:
            break;
    }
    return 0;
}

int main(void) {
    Grid grid = load_from_file(GRID_SIZE, "../day04/input");
    print_grid(&grid);
    size_t total = 0;
    for (u_int8_t r = 0; r < GRID_SIZE; ++r) {
        for (u_int8_t c = 0; c < GRID_SIZE; ++c) {
            for (u_int8_t i = 1; i <= 8; ++i) {
                total += isXmas(&grid, r, c, i, 0, 1);
                total += isXmas(&grid, r, c, i, 3, -1);
            }
        }
        printf("\n");
    }
    printf("Total 'XMAS' sequences: %zu", total);
    deconstruct_grid(&grid);
}
