#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"

//Renvoie un reseau vide
Reseau *creer_reseau(){
    Reseau* reseau = (Reseau*)malloc(sizeof(Reseau));
    reseau->nbNoeuds = 0;
    reseau->gamma = 0;
    reseau->noeuds = NULL;
    reseau->commodites = NULL;
    return reseau;
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

//Ajoute voisin aux voisins de n
void ajouter_voisin(Noeud* n, Noeud* voisin){
    if(voisin == NULL || n == voisin){ 
        return; 
    }

    CellNoeud* liste_voisin = n->voisins; //on recupère la liste des voisins

    while(liste_voisin){ //on vérifie si voisin est parmis les voisins
        if(liste_voisin->nd == voisin){ //si oui, CellNoeud contient le même noeud voisin
            return;
        }
        liste_voisin = liste_voisin->suiv;
    }

    CellNoeud* new_voisin = creer_cell_noeud(); //sinon on crée le CellNoeud et on ajoute le noeud
    new_voisin->nd = voisin; 

    new_voisin->suiv = n->voisins; //on insère le voisin dans la liste des voisins
    n->voisins = new_voisin; 

    return;
}

//Retourne le noeud de R correspondant, sinon créer le noeud et l'ajoute dans R
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
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
    R->nbNoeuds = R->nbNoeuds + 1;
    Noeud* new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds;
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
    return new_noeud;
}

Reseau* reconstitueReseauListe(Chaines *C){
    //Création du reseau
    Reseau* reseau = creer_reseau();
    reseau->gamma = C->gamma;

    //On recupère les chaines de la Chaine C
    CellChaine* liste = C->chaines;

    //On parcourt toutes les chaines
    while(liste){
        //On crée la commodité
        CellCommodite* commodite = creer_cell_commodite();
        
        CellPoint* liste_points = liste->points;  //liste des points dans la chaine
        CellPoint* precedant = liste_points, *suiv = NULL; //On garde le precedant et le suivant

        //Premier point, on le cherche et le rajoute s'il n'est pas dans le réseau
        Noeud* n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y); 

        commodite->extrA = n; 

        //On parcourt tous les CellPoints
        while(liste_points->suiv != NULL){
            suiv = liste_points->suiv; 
            Noeud* n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);

            //Ajout des voisins au noeud n2
            ajouter_voisin(n,rechercheCreeNoeudListe(reseau, precedant->x, precedant->y));
            ajouter_voisin(n,rechercheCreeNoeudListe(reseau, suiv->x, suiv->y));

            //on passe au point suivant
            precedant = liste_points;
            liste_points = liste_points->suiv; 
        }

        commodite->extrB = rechercheCreeNoeudListe(reseau,liste_points->x, liste_points->y);
        //on rajoute le voisin précédant vu qu'on est dans l'extremité B
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudListe(reseau, precedant->x, precedant->y));

        //inserer la commodite au reseau
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite; 
        
        //On a rajoute la commodite et le noeud de la chaine au réseau, donc on passe à la chaine suivante

        liste = liste->suiv; 
    }
    //on retourne le reseau
    return reseau; 
}