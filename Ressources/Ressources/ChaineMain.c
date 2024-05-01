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
    printf("\nLongueur physique totale des chaînes : %.4f\n",longueurTotale(chaines));
    printf("Nombre total de points : %d\n",comptePointsTotal(chaines));
    printf("Un fichier 'chaine.html a été créé dans votre répertoire\n");
    afficheChainesSVG(chaines,"chaine"); 

    int rep;
    printf("\nSouhaitez-vous écrire cette chaine sur autre fichier ? si oui taper 1 sinon taper 0 : ");scanf(" %d", &rep);
    if(rep==1){
        FILE *f2 = fopen("testChaine.txt", "w");
        printf("Un fichier 'testChaine.txt' a été créé dans votre répertoire.\n");
        ecrireChaines(chaines, f2);
        fclose(f2); 
        printf("\nFin du programme.\n");
    }else{
        printf("\nFin du programme.\n");
    }
    liberer_Chaines(chaines);
    return 0; 
}