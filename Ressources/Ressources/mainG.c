#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"



int main(){
   
    //FILE *f = fopen("00014_burma.cha", "r"); 
    FILE *f = fopen("05000_USA-road-d-NY.cha", "r"); 
    //FILE *f = fopen("07397_pla.cha", "r"); 

    
    Chaines* test = lectureChaines(f);
    Reseau* r_lc = reconstitueReseauListe(test);
    int val = reorganiseReseau(r_lc);
    liberer_Chaines(test);
    liberer_reseau(r_lc);
    

    //Reseau* r = reconstitueReseauListe(test); 
    //int val = reorganiseReseau(r);
   /* Graphe* g = creerGraphe(r);
    Cell_entier* l =  arborescence_chemins(g,u,v);
    
    if(l==NULL){
        printf("liste null\n");
    }
    while(l){
        printf("num: %d \n",l->num);
        l = l->suiv;
    }
    int chemin = plus_petit_nb_aretes(g,u,v);
    printf("la lg du plus petit chemin entre %d et %d est %d\n",u,v,chemin);*/
/*
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

    */
    return 0;
}
