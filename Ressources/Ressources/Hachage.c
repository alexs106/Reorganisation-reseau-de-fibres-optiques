#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include <math.h>

TableHachage* creation_table_hachage(int tailleM){
    TableHachage* t = malloc(sizeof(TableHachage));
    t->nbElement = 0;
    t->tailleMax = tailleM;
    t->T = malloc(sizeof(CellNoeud)*tailleM);
    return t;
}

int cle(double x,double y){
    int res = (y+(x+y)*(x+y+1))/2;
    return res; 
}

int hachage(int k,TableHachage* h){
    int M = h->tailleMax;
    double A = (sqrt(5)-1)/2;
    int tmp = k*A; 
    return M * (k*A - tmp); 
}

//A TESTER, ELLE COMPILE
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y){
    
    int c = cle(x,y);
    int indice = hachage(c,H);

    CellNoeud* cell_n = H->T[indice];

    while(cell_n != NULL){
        Noeud* n = cell_n->nd;
        if((n->x == x) && (n->y == y)){
            return n;
        }
        cell_n = cell_n->suiv;
    }
    //Création du noeud
    Noeud* new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds;
    new_noeud->voisins = NULL;

    //Création de la cellule noeud
    CellNoeud* new_celln = creer_cell_noeud();
    new_celln->nd = new_noeud;
    new_celln->suiv = NULL; 

    //Ajout dans la table de hachage
    new_celln->suiv = H->T[indice];
    H->T[indice] = new_celln;

    //Ajout dans le réseau
    R->nbNoeuds = R->nbNoeuds + 1;
    R->noeuds = ajout_noeud(R->noeuds, new_celln);
    
    return new_noeud;
}

