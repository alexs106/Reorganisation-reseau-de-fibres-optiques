#include "Reseau.h"
#include "Chaine.h"
#include <stdio.h>

int main(int argc,char** argv){
    printf("Pour obtenir la méthode 1 taper: le chiffre 1\n");
    printf("Pour obtenir la méthode 2 taper: le chiffre 2\n");
    printf("Pour obtenir la méthode 3 taper: le chiffre 3\n");

    char* nom_fichier = argv[1];
    int num_meth = argv[2];
    FILE *f = fopen(nom_fichier, "r");
    Chaines * chaine = lectureChaines(f); 

    if(num_meth == 1){
        
    }


}