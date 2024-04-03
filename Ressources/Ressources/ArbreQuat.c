#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include <math.h>

/*Fonction qui détermine les coordonnées minimales et maximales 
des points des chaînes du réseau */
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
    CellChaine* chaines = C->chaines;
    CellPoint* points = chaines->points; 
    //On donne les valeurs du premier points au min et max
    *xmin = points->x;
    *xmax = points->x;
    *ymin = points->y;
    *ymax = points->y; 

    while(chaines != NULL){ //On parcourt les chaines
        points = chaines -> points;
        while(points){ //On parcourt les points
            //On vérifie si les premières valeurs stockées sont bien les min et max
            //Sinon, on les remplace
            if(points->x < *xmin) *xmin = points->x;
            if(points->x > *xmax) *xmax = points->x;
            if(points->y < *ymin) *ymin = points->y;
            if(points->y > *ymax) *ymax = points->y; 
        }
        chaines = chaines->suiv;
    }
}

/*Fonction qui crée un Arbre Quaternaire et initialise le noeud et les arbres à NULL*/
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
    ArbreQuat* aq = (ArbreQuat*)malloc(sizeof(ArbreQuat));
    aq->xc = xc;
    aq->yc = yc;
    aq->coteX = coteX;
    aq->coteY = coteY;

    aq->noeud = NULL;
    aq->no = NULL;
    aq->ne = NULL;
    aq->so = NULL;
    aq->se = NULL; 
    return aq; 
}

/*Fonction qui permet d'insérer un Noeud du réseau dans un arbre quaternaire*/
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
    
    /*Cas de l'arbre vide*/
    if(*a == NULL){
        double xc;
        double yc;
        
        //Trouver les coordonnées du centre

        //Si le x du noeud est plus petit que celui du parent
        //On se place à l'ouest (JE CROIS!) -> VERIFER 
        if(n->x < parent->xc){
            xc = parent->xc - (parent->coteX/4);
        }else{ //Sinon, on se place à l'est
            xc = parent->xc + (parent->coteX/4);
        }

        //Si le y du noeud est plus petit que celui du parent
        //On se place au sud
        if(n->y < parent->yc){
            yc = parent->yc - (parent->coteY/4);
        }else{ //Sinon, on se place au nord 
            yc = parent->yc + (parent->coteY/4); 
        }

        //Création de l'arbre quaternaire
        *a = creerArbreQuat(xc,yc,parent->coteX/2,parent->coteY/2);

        (*a)->noeud = n; 
    }

    /*Cas de feuille*/
    if ((*a)->noeud != NULL){ //CHECK CONDITION
        Noeud *tmp = (*a)->noeud;

        (*a)->noeud = NULL; //La feuille devient la cellule interne

        insererNoeudArbre(n,a,parent);
        insererNoeudArbre(tmp,a,parent);
    }

    /*Cas de cellule interne*/
    if ((*a != NULL) && ((*a)->noeud == NULL)){
        //Completer 

        if(n->x < (*a)->xc){ //insertion du noeud à l'ouest
            if(n->y < (*a)->yc){ //
                insererNoeudArbre(n, &((*a)->so),*a); //insertion du noeud dans le sous-arbre so
            }else{
                insererNoeudArbre(n,&((*a)->no),*a); //insertion du noeud dans le sous-arbre no
            }
        }else{ //insertion du noeud à l'est 
            if(n->y < (*a)->yc){
                insererNoeudArbre(n, &((*a)->se),*a); //insertion du noeud dans le sous-arbre se
            }else{
                insererNoeudArbre(n, &((*a)->ne),*a); //insertion du noeud dans le sous-arbre ne
            }
        }
    } 
} 
