#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"

int main(){
   
    FILE *f = fopen("00014_burma.cha", "r"); 
    Chaines * test = lectureChaines(f);

    Reseau* r = reconstitueReseauListe(test); 
    Graphe* g = creerGraphe(r);
    return 0;
}
