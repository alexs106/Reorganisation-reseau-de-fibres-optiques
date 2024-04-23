#include "Graphe.h"
#include "Reseau.h"
Graphe* creerGraphe(Reseau* r){
    Graphe* g = (Graphe *)malloc(sizeof(Graphe));

    g->nbsom = r->nbNoeuds;
    g->gamma = r->gamma;
    g->nbcommod = r->commodites;

    //Création du tableau des commodites.
    int nb_commodites = nbCommodites(r);
    Commod* tab_commod = malloc(sizeof(Commod) * nb_commodites);
    
    CellCommodite* lc_commo = r->commodites;
    int i = 0;
    while(lc_commo != NULL && i<nb_commodites){
        tab_commod[i]->e1 = lc_commo->extrA;
        tab_commod[i]->e2 = lc_commo->extrB;
        i++;
        lc_commo = lc_commo->suiv;
    }

    g->T_commod = tab_commod;

    //Création du tableau de pointeurs sur sommets
    int nb_noeuds = r->nbNoeuds;
    Sommet** Tab_som = malloc(sizeof(Sommet)*nb_noeuds);

    CellNoeud* lc_noeuds = r->noeuds;

    while(lc_noeuds != NULL && i<nb_noeuds){
        Tab_som[i]->num = lc_noeuds->nd->num;
        Tab_som[i]->x = lc_noeuds->nd->x;
        Tab_som[i]->y = lc_noeuds->nd->y;


        CellNoeud* lc_voisin_res = lc_noeuds->nd->voisins;
        while(lc_voisin_res!=NULL){
            Cellule_arete* lc_voisin = malloc(sizeof(Cellule_arete));
            lc_voisin->a->u = lc_noeuds->nd->num;
            lc_voisin->a->v = lc_voisin_res->num;
        }


    }   
    



}