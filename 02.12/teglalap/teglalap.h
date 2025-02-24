#ifndef TEGLALAP_H
#define TEGLALAP_H

#include <stdio.h>

typedef struct teglalap
{
    double x,y;
}teglalap;

void create_rectangle(teglalap rect[4], double width, double height);

void rotate_rectangle(teglalap rect[4], double angle);

void print_rectangle(teglalap rect[4]);


#endif