#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"

int main(){
   
    FILE *f = fopen("00014_burma.cha", "r"); 
    Chaines * test = lectureChaines(f);

    Reseau* r = reconstitueReseauListe(test); 
    Graphe* g = creerGraphe(r);

//TEST DE LA QUESTION 7.1
    int i=0;
    while(i<g->nbsom-1){
        int s = g->T_som[i]->num;
        double x = g->T_som[i]->x;
        double y = g->T_som[i]->y;
        printf("sommet : %d x=%.2f et y=%.2f\n",s,x,y);
        Cellule_arete* voisin = g->T_som[i]->L_voisin;
        while(voisin){
            printf("arrete entre u=%d et v=%d\n",voisin->a->u,voisin->a->v);
            voisin = voisin->suiv;
        }
        i++;
    }

    int u = 1;
    int v = 8;
    int chemin = plus_petit_nb_aretes(g,u,v);
    printf("la lg du plus petit chemin entre %d et %d est %d\n",u,v,chemin);
    return 0;
}
