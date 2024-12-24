//
// Created by nicom on 18/11/2021.
//

#ifndef GRID_H
#define GRID_H

typedef struct Grid Grid;
struct Grid {
    int size;
    int* list;
};

typedef enum PointStatus PointStatus;
enum PointStatus {
    X = 'X',
    M = 'M',
    A = 'A',
    S = 'S',
    NOTHING = '.',
    EMPTY = '0'
};

Grid load_from_file(int size, char * fileName);
void deconstruct_grid(const Grid* grid);

void print_grid(const Grid* grid);
PointStatus getValue(const Grid* grid, int x, int y);

#endif