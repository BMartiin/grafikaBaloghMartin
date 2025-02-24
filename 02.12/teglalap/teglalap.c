#include "teglalap.h"

#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

void create_rectangle(teglalap rect[4], double width, double height){
    rect[0] = (teglalap){0, 0};
    rect[1] = (teglalap){width, 0};
    rect[2] = (teglalap){width, height};
    rect[3] = (teglalap){0, height};
}

void rotate_rectangle(teglalap rect[4], double angle){
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);
    
    for (int i = 0; i < 4; i++) {
        double x_new = rect[i].x * cosA - rect[i].y * sinA;
        double y_new = rect[i].x * sinA + rect[i].y * cosA;
        rect[i].x = x_new;
        rect[i].y = y_new;
    }
}

void print_rectangle(teglalap rect[4]){
    for (int i = 0; i < 4; i++) {
        printf("(%lf, %lf)\n", rect[i].x, rect[i].y);
    }
}

