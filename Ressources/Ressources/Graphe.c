#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"

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

/*Fonction qui calcule le plus petit nombre d'arêtes d'une */
int plus_petit_nb_aretes(Graphe* g, int u, int v){
    if(u==v){
        return 0; //chemin null
    }

    int *distance = malloc(sizeof(int) * (g->nbsom));
    int *visite = (int*)malloc(sizeof(int)*(g->nbsom)); 

    for(int i = 0; i<g->nbsom; i++){
        visite[i] = 0;
        distance[i] = 0;
    }
    
    visite[u] = 1;
    S_file *f = (S_file*) malloc(sizeof(S_file));
    
    Init_file(f);
    enfile(f,u);
    while(! (estFileVide(f))){
        int val = defile(f);
        Cellule_arete *val_courante = g->T_som[u] -> L_voisin;
        while(val_courante){
            int d;
            if(val_courante->a->u == val){
                d = val_courante->a->v;
            }else{
                d = val_courante->a->u;
            }
            if(visite[d]==0){
                visite[d] = 1;
                distance[d] = distance[val]+1;
                enfile(f,d); 
            }
            val_courante = val_courante->suiv;
        }
    }
    int res = distance[v];
    free(visite);
    free(f);
    free(distance);
    return res; 
}

/*Fonction qui libère les sommets d'une Table de Sommets*/
void liberer_sommets(Sommet **T_som, int nbsom){
    for(int i = 0; i<nbsom; i++){
        if(T_som[i]!=NULL){
            while(T_som[i]->L_voisin){
                Cellule_arete *ca = T_som[i]->L_voisin->suiv;
                liberer_arete(T_som[i]->L_voisin);
                T_som[i]->L_voisin=ca;
            }
            free(T_som[i]);
            T_som[i]=NULL;
        }
    }
    free(T_som); 
}

/*Fonction qui libère les arêtes d'une cellule d'arêtes*/
void liberer_arete(Cellule_arete *ca){
    if(ca == NULL){
        return 0;
    }
    if(ca->a->u == -1 && ca->a->v == -1){
        free(ca->a);
    }else{
        ca->a->u = -1;
        ca->a->v = -1;
    }
    free(ca);
}

/*Fonction qui libère le graphe*/
void liberer_graphe(Graphe *g){
    liberer_sommet(g->T_som,g->nbsom);
    free(g->T_commod);
    free(g); 
}