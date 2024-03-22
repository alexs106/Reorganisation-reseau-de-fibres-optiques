#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"

//Renvoie un reseau vide
Reseau *creer_reseau(){
    Reseau* reseau = (Reseau*)malloc(sizeof(Reseau));
    reseau->nbNoeuds = 0;
    reseau->gamma = 0;
    reseau->noeuds = NULL;
    reseau->commodites = NULL;
}

//Renvoie une commodité vide
CellCommodite* creer_cell_commodite(){
    CellCommodite* cellc = (CellCommodite*)malloc(sizeof(CellCommodite));
    cellc->extrA = NULL;
    cellc->extrB = NULL;
    cellc->suiv = NULL;
    return cellc;
}

//Renvoie un CellNoeud vide
CellNoeud* creer_cell_noeud(){
    CellNoeud* celln = (CellNoeud*)malloc(sizeof(CellNoeud));
    celln->nd = NULL;
    celln->suiv = NULL;
    return celln; 
}

//Renvoie un noeud vide
Noeud* creer_noeud(){
    Noeud* n = (Noeud*)malloc(sizeof(Noeud));
    n->num = 0;
    n->x = 0;
    n->y = 0;
    n->voisins = NULL;
    return n; 
}
/*
//Ajoute voisin aux voisins de n
void ajouter_voisin(Noeud* n, Noeud* voisin){
    if(voisin == NULL || n = voisin){ //POURQUOI UNE ERREUR?????
        return ;
    }

    CellNoeud* liste_voisin = n->voisins; //on recupère la liste des voisins

    while(liste_voisin){ //on vérifie si voisin est parmis les voisins
        if(liste_voisin->nd == voisin){ //si oui, CellNoeud contient le même noeud voisin
            return ;
        }
        liste_voisin = liste_voisin->suiv;
    }

    CellNoeud* new_voisin = creer_cell_noeud(); //sinon on crée le CellNoeud et on ajoute le noeud
    new_voisin->nd = voisin; 

    new_voisin->suiv = n->voisins; //on insère le voisin dans la liste des voisins
    n->voisins = new_voisin; 

    return ;
}
*/

//Retourne le noeud de R correspondant, sinon créer le noeud et l'ajoute dans R
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
   /* CellNoeud* liste = R->noeuds; //PARTIE D'alex

    while(liste != NULL){
        if((liste->nd->x == x) && (liste->nd->y == y)){
            return liste->nd; 
        }
        liste = liste->suiv;
    }

    //dans le cas o`u le noeud n'existe pas, on le créé
    Noeud* new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds +1;

    //création de la cellule
    CellNoeud* new_celln = (CellNoeud*) malloc(sizeof(CellNoeud));
    new_celln->nd = new_noeud; //on affecte le noeud dans la cellule
    new_celln->suiv = R->noeuds; //on ajoute à la suite de la liste 
    // A verifier !!!

    R->noeuds = new_celln;
    //ajout de R
    //A COMPLETER, COURAGE NOAH ;)
    */

    CellNoeud* cell_noeuds = R->noeuds;
    if(cell_noeuds != NULL){ //on regarde si le premier élément est NULL.
        if((cell_noeuds->nd->x == x) && (cell_noeuds->nd->y == y)){ //on regarde si le premier l'élément contient les paramètres x et y.
            return cell_noeuds->nd; 
        }
        else{
            while(cell_noeuds->suiv != NULL){ //on parcourt la liste temps que son suivant n'est pas NULL.
                if((cell_noeuds->nd->x == x) && (cell_noeuds->nd->y == y)){ // on fait la comparaison.
                    return  cell_noeuds->nd;
                }
                cell_noeuds = cell_noeuds->suiv;
            }
            if((cell_noeuds->nd->x == x) && (cell_noeuds->nd->y == y)){
                return cell_noeuds->nd;
            }
        }
    }

    /*si les paramètres x et y ne sont pas présent dans liste, on va alors créer une nouvelle struc Noeud et une nouvelle struc CellNoeud.
    Puis ajouter CellNoeud à la fin de la liste ou au début si elle est vide. */
    Noeud* new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds + 1;
    new_noeud->voisins = NULL;

    CellNoeud* new_celln = (CellNoeud*) malloc(sizeof(CellNoeud));
    new_celln->nd = new_noeud; //on affecte le noeud dans la cellule
    new_celln->suiv = NULL;

    if(cell_noeuds == NULL){ // on est dans le cas ou cell_noeuds ne contient pas de noeuds.
        R->noeuds = new_celln;
    }
    else{
        cell_noeuds->suiv = new_celln; 
    }
    return NULL;
}