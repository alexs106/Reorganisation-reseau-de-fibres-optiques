#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "SVGwriter.h"

int main(int argc,char** argv){
    if(argc != 2){
        printf("Usage: %s fichier.cha\n",argv[0]);
        return 1;
    }
    char* nom_fichier = argv[1];
    FILE* f = fopen(nom_fichier, "r");
    Chaines* chaines = lectureChaines(f); //construction de la chaine.
    printf("Longueur physique totale des chaînes : %.4f\n",longueurTotale(chaine));
    printf("Nombre total de point : %d\n",comptePointsTotal(chaine));

    printf("Souhaitez-vous écrire cette chaine sur autre fichier ? si oui tapez 1 sinon 0\n")
    printf("")




    //FILE *f = fopen("00014_burma.cha", "r");
    //FILE *f2 = fopen("testChaine.txt", "w"); 
    Chaines * chaines = lectureChaines(f);
    ecrireChaines(test_chaine, f2); 
   
    printf("%.4f\n",longueurTotale(test_chaine));
    printf("%d\n",comptePointsTotal(test_chaine));
    
    afficheChainesSVG(test_chaine,"chaine"); 

    liberer_Chaines(test_chaine);
    fclose(f2); 
    return 0; 

}