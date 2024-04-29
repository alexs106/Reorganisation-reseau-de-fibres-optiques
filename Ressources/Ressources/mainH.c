#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include <stdio.h>

int main(){
    FILE *f = fopen("05000_USA-road-d-NY.cha", "r"); 
    Chaines * test_chaine = lectureChaines(f);

    Reseau* r = reconstitueReseauHachage(test_chaine,10);
    FILE *fw = fopen("test_hachage.txt", "w"); 
    //ecrireReseau(r,fw);
    //afficheReseauSVG(r,"hachage"); 

    //Libération de mémoire
    liberer_reseau(r);
    liberer_Chaines(test_chaine);  

    fclose(fw); 

    /*test pour le noeud 12
    int k = cle(16.53,97.38);
    printf("cle : %d\n",k);
    printf("indice : %d\n",hachage(k,t)); //indice 6 

    //test pour le noeud 11 
    int k2 = cle(25.23,97.24);
    printf("cle : %d\n",k2);
    printf("indice : %d\n",hachage(k2,t)); //indice 6

    //test pour le noeud 10
    int k3 = cle(20.09,94.55);
    printf("cle : %d\n",k3);
    printf("indice : %d\n",hachage(k3,t)); //indice 3
    */
   /* Noeud * n12 = rechercheCreeNoeudHachage(R,t, 16.53, 97.38);
    Noeud * n11 = rechercheCreeNoeudHachage(R,t, 25.23, 97.24);

   CellNoeud* c = t->T[6]; 
   while(c != NULL){
    printf("num= %d x=%.2f,y=%.2f\n",c->nd->num,c->nd->x,c->nd->y);
    c =c->suiv;
   }*/



//EXERCICE 4 FAIRE LE TEST DE LA QUESTION 4 !!!!!!

    for(int x=1; x<=10;x++){
        for(int y=1; y<=10; y++){
            printf("x=%d ,y =%d, cle= %d\n", x, y, cle(x,y)); 
        }
    }

    return 0; 
}