#include "Reseau.h"
#include "Chaine.h"
#include <stdio.h>

int main(){
    Reseau* R = creer_reseau();
    Noeud* n1 = rechercheCreeNoeudListe(R,1,1);
    Noeud* n2 = rechercheCreeNoeudListe(R,2,2);
    Noeud* n3 = rechercheCreeNoeudListe(R,3,1);
    //CellNoeud* c = R->noeuds;

    FILE *f = fopen("00014_burma.cha", "r"); 
    Chaines * test = lectureChaines(f);

    Reseau* r2 = reconstitueReseauListe(test); 
    CellNoeud* c = r2->noeuds;
    //c= c->suiv->suiv; 

    //afficheChainesSVG(test,"testRes"); //REGARDER
    /*
    while(c){
        printf("x=%.2f y=%.2f num=%d\n",c->nd->x,c->nd->y,c->nd->num);
        CellNoeud* v = c->nd->voisins;
        printf("Voisins\n"); 
        while(v){
            printf("x=%.2f y=%.2f num=%d\n",v->nd->x,v->nd->y,v->nd->num);
            v = v->suiv;
        }
        c=NULL;
    }
    */
   //int nb = nbLiaisons(r2); 
   int nb = nbCommodites(r2); 
   printf("%d\n", nb); 

    return 0;
    
}