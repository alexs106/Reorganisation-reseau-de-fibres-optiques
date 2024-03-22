#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "SVGwriter.h"

int main(){
    FILE *f = fopen("00014_burma.cha", "r");
    FILE *f2 = fopen("test.txt", "w"); 
    Chaines * test = lectureChaines(f);
    ecrireChaines(test, f2); 
    printf("%.4f\n",longueurTotale(test));
    printf("%d\n",comptePointsTotal(test));
   
    afficheChainesSVG(test,"test"); 
    return 0; 
}