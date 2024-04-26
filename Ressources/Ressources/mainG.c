#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"

int main(){
   
    int u = 7;
    int v = 8;
    FILE *f = fopen("00014_burma.cha", "r"); 
    Chaines * test = lectureChaines(f);

    Reseau* r = reconstitueReseauListe(test); 
    Graphe* g = creerGraphe(r);
    Cell_entier* l =  arborescence_chemins(g,u,v);

    if(l==NULL){
        printf("liste null\n");
    }
    while(l){
        printf("num: %d \n",l->num);
        l = l->suiv;
    }
    int chemin = plus_petit_nb_aretes(g,u,v);
    printf("la lg du plus petit chemin entre %d et %d est %d\n",u,v,chemin);

//TEST DE LA QUESTION 7.1
   /* int i=0;
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

    */
    return 0;
}
