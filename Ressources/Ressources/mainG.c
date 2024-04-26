#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"

int main(){
   
    FILE *f = fopen("00014_burma.cha", "r"); 
    Chaines * test = lectureChaines(f);

    Reseau* r = reconstitueReseauListe(test); 
    Graphe* g = creerGraphe(r);
/*
    int s = g->T_som[0]->num;
    double x = g->T_som[0]->x;
    double y = g->T_som[0]->y;
    printf("sommet : %d x=%.2f et y=%.2f\n",s,x,y);
    Cellule_arete* voisin = g->T_som[0]->L_voisin;
    if(voisin==NULL){
        printf("la liste des voisins est null\n");
    }
    while(voisin!=NULL){
        printf("arrete u=%d et v=%d\n",voisin->a->u,voisin->a->v);
        voisin = voisin->suiv;
    }
    */

    return 0;
}
