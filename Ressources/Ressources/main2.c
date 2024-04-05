#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include <stdio.h>

int main(){
    Reseau* R = creer_reseau();
    //Noeud* n1 = rechercheCreeNoeudListe(R,1,1);
    //Noeud* n2 = rechercheCreeNoeudListe(R,2,2);
    //Noeud* n3 = rechercheCreeNoeudListe(R,3,1);
    //CellNoeud* c = R->noeuds;

    FILE *f = fopen("00014_burma.cha", "r"); 
    Chaines * test = lectureChaines(f);

    Reseau* r2 = reconstitueReseauListe(test); 
    
    FILE *fw = fopen("test_res.txt", "w"); 
    ecrireReseau(r2,fw);
    afficheReseauSVG(r2,"reseau"); 
    /*int nb_l = nbLiaisons(r2); 
    int nb_c = nbCommodites(r2); 
    printf("nombre de liaisons : %d\n", nb_l); 
    printf("nombre de Commodites: %d\n", nb_c);*/ 



    //Libération de mémoire
    liberer_reseau(R);
    liberer_reseau(r2);
    liberer_Chaines(test);  

    //CellNoeud* c = r2->noeuds;

    //c= c->suiv->suiv; 
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
   //int nb = nbCommodites(r2); 
   //printf("%d\n", nb); 

    return 0;
    
}