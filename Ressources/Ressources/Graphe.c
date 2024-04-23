#include "Graphe.h"
#include "Reseau.h"

Sommet* creer_sommet(int num,double x,double y){
    Sommet* s = (Sommet*) malloc(sizeof(Sommet));
    s->num = num;
    s->x = x;
    s->y = y;
    s->L_voisin = NULL;
    return s; 
}

Arete* creer_arete(int u, int v){
    Arete* a = malloc(sizeof(Arete));
    a->u = u;
    a->v = v;
    return a; 
}

Graphe* creerGraphe(Reseau* r){
    Graphe *g = (Graphe *)malloc(sizeof(Graphe));

    g->nbsom = r->nbNoeuds; 
    g->gamma = r->gamma;
    g->nbcommod = nbCommodites(r); //nb de commodites dans le réseau r.
    g->T_som = (Sommet**) malloc(sizeof(Sommet*)*g->nbsom); 

    //Création du tableau des commodites.
    CellCommodite* lc_commo = r->commodites; //récupération de la liste des commodites du réseau r.

    g->T_commod = (Commod*)malloc(sizeof(Commod) * g->nbcommod); //allocation du tableau des commodites.
    
    int i = 0;
    //printf("nb commodites : %d\n",nb_commodites);
    while(lc_commo != NULL){ 
        (g->T_commod)[i].e1 = lc_commo->extrA->num;
        //printf("extaA %d\n",lc_commo->extrA->num);
        (g->T_commod)[i].e2 = lc_commo->extrB->num;
        //printf("extaB %d\n",lc_commo->extrB->num);
        i++;
        lc_commo = lc_commo->suiv;
    }
    
    //Initialisation de tous les sommets avec coordonnées
    CellNoeud* lc_noeuds = r->noeuds;
    while(lc_noeuds!=NULL){
        Noeud* noeud = lc_noeuds->nd;
        (g->T_som)[(lc_noeuds->nd->num)-1] = creer_sommet(noeud->num,noeud->x,noeud->y);
        lc_noeuds = lc_noeuds->suiv;
    }

    lc_noeuds = r->noeuds;
    while(lc_noeuds != NULL){
        Noeud* noeud = lc_noeuds->nd;
        CellNoeud* lc_noeudsvoisin = noeud->voisins;

        while(lc_noeudsvoisin != NULL){
            Noeud* noeudvoisin = lc_noeudsvoisin->nd;
            if(noeud->num < noeudvoisin->num){
                //Créer arrête
                Arete* arete = creer_arete(noeud->num,noeudvoisin->num); 

                Cellule_arete* lc_arete = malloc(sizeof(Cellule_arete));
                lc_arete->a = arete; 

                lc_arete->suiv = g->T_som[(arete->u)-1]->L_voisin;
                g->T_som[(noeud->num)-1]->L_voisin = lc_arete->suiv; 
                
            }
            lc_noeudsvoisin = lc_noeudsvoisin->suiv;
        }
        lc_noeuds = lc_noeuds->suiv; 

    }
    return g;
}
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
