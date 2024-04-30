#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include <stdlib.h>
#include <stdio.h>
#include "Struct_File.h"
#include "Reseau.h"



typedef struct{
    int u,v; /* Numeros des sommets extremite */
}Arete;

typedef struct cellule_arete {
    Arete * a ;
    /* pointeur sur l’arete */
    struct cellule_arete * suiv ;
}Cellule_arete;

typedef struct {
    int num ;
    /* Numero du sommet (le meme que dans T_som) */
    double x , y ;
    Cellule_arete * L_voisin ; /* Liste chainee des voisins */
}Sommet ;

typedef struct {
    int e1 , e2 ;
    /* Les deux extremites de la commodite */
}Commod ;

typedef struct{
    int nbsom ; /* Nombre de sommets */
    Sommet** T_som ; /* Tableau de pointeurs sur sommets */
    int gamma ;
    int nbcommod; /* Nombre de commodites */
    Commod* T_commod ; /* Tableau des commodites */
}Graphe;

typedef struct Cell_entier{
    int num;
    struct Cell_entier *suiv; 
}Cell_entier; 

typedef struct liste_commodite{
    int num; //numéro de la commodite.
    Commod c; //Les deux extremites de la commodite
    Cell_entier* chaine; //la chaine la plus courte pour la commodite.
    struct liste_commodite* suiv;
}LC_commo;



Graphe* creerGraphe(Reseau* r);
Sommet* creer_sommet(int num,double x,double y); 
Arete* creer_arete(int u, int v); 

int plus_petit_nb_aretes(Graphe* g, int u, int v);
Cell_entier* arborescence_chemins(Graphe* g, int u, int v);
int reorganiseReseau(Reseau* r);

void liberer_file(S_file *f); 
void liberer_sommets(Sommet **T_som, int nbsom);
void liberer_arete(Cellule_arete *ca);
void liberer_graphe(Graphe *g);

# endif