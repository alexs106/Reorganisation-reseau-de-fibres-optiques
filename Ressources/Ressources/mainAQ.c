#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f = fopen("00014_burma.cha", "r"); 
    Chaines * test_aq = lectureChaines(f);

    Reseau* r = reconstitueReseauArbre(test_aq);
    FILE *fw = fopen("test_Arbre.txt", "w"); 
    ecrireReseau(r,fw); 
    afficheReseauSVG(r,"arbreq");
    return 0; 
}