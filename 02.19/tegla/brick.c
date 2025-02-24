#include "brick.h"

#include <math.h>

void set_size(Brick* brick, double x, double y, double z){ 
    brick->x=x;
    brick->y=y;
    brick->z=z;
}

double calc_volume(Brick* brick){
    return brick->x*brick->y*brick->z;
}

double calc_surface(Brick* brick){
    return 2*(brick->x*brick->y + brick->y*brick->z + brick->x*brick->z);
}

int has_sqr_side(Brick* brick){
    if (brick->x==brick->y || brick->x==brick->z || brick->y==brick->z)
    {
        return 1;
    }
    else{
        return 0;
    }
    
}
