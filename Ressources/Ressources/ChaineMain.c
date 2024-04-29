#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "SVGwriter.h"

int main(){
    FILE *f = fopen("00014_burma.cha", "r");
    FILE *f2 = fopen("test.txt", "w"); 
    Chaines * test_chaine = lectureChaines(f);
    ecrireChaines(test_chaine, f2); 
   
    printf("%.4f\n",longueurTotale(test_chaine));
    printf("%d\n",comptePointsTotal(test_chaine));
    
    afficheChainesSVG(test_chaine,"chaine"); 

    liberer_Chaines(test_chaine);
    fclose(f2); 
    return 0; 

}