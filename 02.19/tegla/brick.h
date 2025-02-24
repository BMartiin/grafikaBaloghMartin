#ifndef BRICK_H
#define BRICK_H

#include <stdio.h>

typedef struct Brick
{
    double x,y,z;
}Brick;

void set_size(Brick* brick, double x, double y, double z);

double calc_volume(Brick* brick);

double calc_surface(Brick* brick);

int has_sqr_side(Brick* brick);

#endif