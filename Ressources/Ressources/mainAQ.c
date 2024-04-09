#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    //FILE *f = fopen("00014_burma.cha", "r"); 
    //Chaines * test = lectureChaines(f);
   
    /*TEST POUR LA QUESTION 5.1 CODE EST BON !!!!
    double x_min = 0;
    double x_max = 0;
    double y_min = 0;
    double y_max = 0;
    chaineCoordMinMax(test,&x_min,&y_min,&x_max,&y_max);
    printf("xmin=%.2f\nymin=%.2f\nxmax=%.2f\nymax=%.2f\n",x_min,y_min,x_max,y_max); 
    */

   /*TEST POUR LA QUESTION 5.2 */
    ArbreQuat* p= creerArbreQuat(10, 10,20, 20);
    Noeud* n = creer_noeud();
    n->x = 15;
    n->y = 15;    
    ArbreQuat*  a= NULL;
    insererNoeudArbre(n, &a, p);
    printf("insertion du noeud quand l'arbre est vide\n");
    printf("xc=%.2f et yc=%.2f\ncoteX=%.2f et coteY=%.2f\n",a->xc,a->yc,a->coteX,a->coteY);

    return 0; 
}