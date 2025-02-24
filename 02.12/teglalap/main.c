#include "teglalap.h"

#include <stdio.h>

int main(){

    teglalap rect[4];
    double width;
    double height;
    double angle;

    printf("Adja meg a teglalap szelesseget: ");
    scanf("%lf", &width);
    printf("Adja meg a teglalap magassagat: ");
    scanf("%lf", &height);
    printf("Adja meg a forgatas szoget fokban: ");
    scanf("%lf", &angle);
   
    create_rectangle(rect,width,height);
    printf("A teglalap koordinatai: ");
    print_rectangle(rect);
    rotate_rectangle(rect,angle);
    printf("A teglalap forgatas utani koordinatai: ");
    print_rectangle(rect);

    return 0;
}