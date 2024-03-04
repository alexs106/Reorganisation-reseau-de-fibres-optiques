#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "SVGwriter.h"

int main(){
    FILE *f = fopen("00014_burma.cha", "r");
    FILE *f2 = fopen("test.txt", "w"); 
    Chaines * test = lectureChaines(f);

    /*
    while(test->chaines){
        printf("%d ",test->chaines->numero);
        while(test->chaines->points){
            printf("%.2f %.2f ",test->chaines->points->y,test->chaines->points->x);
            test->chaines->points = test->chaines->points->suiv;
        }
        printf("\n");
        test->chaines = test->chaines->suiv;
    }
    printf("\n");
    ecrireChaines(test, f2); 

    */ 
   
    afficheChainesSVG(test,"test"); 
    return 0; 
}