#include "brick.h"

#include <stdio.h>

int main(){

    Brick brick;
    double volume, surface, x, y, z;
    int sqr;
    int ih = 0;

    do
    {
        printf("Irja be az x oldal hosszat!: ");
        scanf("%lf", &x);
          
        printf("Irja be az y oldal hosszat!: ");
        scanf("%lf", &y);
           
        printf("Irja be az z oldal hosszat!: ");
        scanf("%lf", &z);

        if(x > 0 && x < 1000 && y > 0 && y < 1000 && z > 0 && z < 1000){
            ih = 1;
        }
        else{
            ih = 0;
            printf("Az ertekknek nagyobbnak kell lennie 0-nal es kisebbnek kell lennie 1000nel");
        }
    } while (!ih);

    set_size(&brick,x,y,z);
    
    volume = calc_volume(&brick);
    printf("A teglatest terfogata: %lf\n",volume);

    surface = calc_surface(&brick);
    printf("A teglatest felszine: %lf\n",surface);

    sqr = has_sqr_side(&brick);

    if(sqr==1){
        printf("A teglatestnek van negyzet alaku oldala \n");
    }
    else{
        printf("A teglatestnek nincs negyzet alaku oldala \n");
    }

    return 0;
}
