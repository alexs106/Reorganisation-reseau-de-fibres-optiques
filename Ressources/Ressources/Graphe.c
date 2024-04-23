#include "Graphe.h"
#include "Reseau.h"

Graphe* creerGraphe(Reseau* r){
  
    Graphe* g = (Graphe *)malloc(sizeof(Graphe));

    g->nbsom = r->nbNoeuds; 
    g->gamma = r->gamma;

    //Création du tableau des commodites.
    CellCommodite* lc_commo = r->commodites; //récupération de la liste des commodites du réseau r.
    //int nb_commodites = nbCommodites(r); //nb de commodites dans le réseau r.
    ///g->nbcommod = nb_commodites; 


    Commod** tab_commod = malloc(sizeof(Commod) * 10); //allocation du tableau des commodites.
     
   
    int i = 0;
    //printf("nb commodites : %d\n",nb_commodites);
    while(lc_commo != NULL && i<10){ 
        tab_commod[i]->e1 = lc_commo->extrA->num;
        tab_commod[i]->e2 = lc_commo->extrB->num;
        i++;
        lc_commo = lc_commo->suiv;
    }
    g->T_commod = tab_commod;
    return g;
    /*
    //Création du tableau de pointeurs sur sommets
    int nb_noeuds = r->nbNoeuds;
    Sommet** Tab_som = malloc(sizeof(Sommet)*nb_noeuds);

    CellNoeud* lc_noeuds = r->noeuds;*/
/*
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
    */

}