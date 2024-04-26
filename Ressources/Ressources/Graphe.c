#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"
#include "Struct_File.h"

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
        //printf("noeud %d\n",noeud->num);
        while(lc_noeudsvoisin != NULL){
            Noeud* noeudvoisin = lc_noeudsvoisin->nd;
            //printf("noeudvoisin : %d\n",noeudvoisin->num);
            if(noeud->num < noeudvoisin->num){
                //Créer arrête
                Arete* arete = creer_arete(noeud->num,noeudvoisin->num); 
               // printf("creation de l'arête entre %d et %d\n",arete->u,arete->v);

                //On rajoute dans la liste voisin du sommet u l'arête {u,v}
                Cellule_arete* lc_arete = malloc(sizeof(Cellule_arete));
                lc_arete->a = arete;

                if(g->T_som[(arete->u)-1]->L_voisin == NULL){
                    lc_arete->suiv = NULL;
                    g->T_som[(arete->u)-1]->L_voisin = lc_arete;
                }
                else{
                    lc_arete->suiv = g->T_som[(arete->u)-1]->L_voisin;
                    g->T_som[(arete->u)-1]->L_voisin = lc_arete;
                }

                //On rajoute dans la liste voisin du sommet v l'arête {u,v}
                Cellule_arete* lc_arete_v = malloc(sizeof(Cellule_arete));
                 lc_arete_v->a = arete;
            
                if(g->T_som[(arete->v)-1]->L_voisin == NULL){
                    lc_arete_v->suiv = NULL;
                    g->T_som[(arete->v)-1]->L_voisin = lc_arete_v;
                }
                else{
                    lc_arete_v->suiv = g->T_som[(arete->v)-1]->L_voisin;
                    g->T_som[(arete->v)-1]->L_voisin = lc_arete_v;
                }
                
                /*

                lc_aretCellule_arete* voisin = g->T_som[1]->L_voisin;e->a = arete; 

                lc_arete->suiv = g->T_som[(arete->u)-1]->L_voisin;
                g->T_som[(noeud->num)-1]->L_voisin = lc_arete->suiv;*/
                
            }
            lc_noeudsvoisin = lc_noeudsvoisin->suiv;
        }
        lc_noeuds = lc_noeuds->suiv; 

    }
    return g;
}



/*Fonction qui calcule le plus petit nombre d'arêtes d'une chaine entre deux sommets u et v d'un graphe. */
int plus_petit_nb_aretes(Graphe* g, int u, int v){
    int *chemin = malloc((g->nbsom)*sizeof(int));

    int *visite = (int*)malloc(sizeof(int)*(g->nbsom)); 

    for(int i = 0; i<g->nbsom; i++){
        visite[i] = 0;
        chemin[i] = 0;
    }

    visite[u-1] = 1;
    chemin[u-1] = 0; 
    S_file *f = (S_file*) malloc(sizeof(S_file));
    
    Init_file(f);
    enfile(f,u);

    while(!(estFileVide(f))){
        int val = defile(f);
        if(val == v){
            liberer_file(f); 
            return chemin[v-1]; 
        }

        Cellule_arete *courante = g->T_som[val-1]->L_voisin;
        while(courante!=NULL){
            int voisin;
            if(val == courante->a->u){
                voisin = courante->a->v;
            }else{
                voisin = courante->a->u; 
            }
            if(visite[voisin-1] == 0){
                visite[voisin-1] = 1;
                enfile(f,voisin);
                chemin[voisin-1] = chemin[val -1] +1; 
            }
    
            courante = courante->suiv; 
        }

    }
    liberer_file(f); 
    return -1; //Pas de chemin
}


Cell_entier* creer_liste_entiers(){
    Cell_entier *L = malloc(sizeof(Cell_entier)); 
    return L; 
}

Cell_entier* ajout_en_tete(Cell_entier *L, int n){
    Cell_entier *nouveau = (Cell_entier*)malloc(sizeof(Cell_entier)); 
    nouveau->num = n;
    nouveau->suiv = L;
    return nouveau; 
}


/*Fonction qui stocke l'arborescence des chemins entre u et v*/
Cell_entier* arborescence_chemins(Graphe* g, int u, int v){
    int *chemin = malloc((g->nbsom)*sizeof(int));
    int *visite = (int*)malloc(sizeof(int)*(g->nbsom)); 
    int *predecesseur = (int*)malloc(sizeof(int)*(g->nbsom)); 

    for(int i = 0; i<g->nbsom; i++){
        visite[i] = 0;
        chemin[i] = 0;
        predecesseur[i] = 0; 
    }

    visite[u-1] = 1;
    chemin[u-1] = 0; 
    S_file *f = (S_file*) malloc(sizeof(S_file));
    
    Init_file(f);
    enfile(f,u);

    while(!(estFileVide(f))){
        int val = defile(f);

        Cellule_arete *courante = g->T_som[val-1]->L_voisin;
        while(courante!=NULL){
            int voisin; 
            if(val == courante->a->u){
                voisin = courante->a->v;
            }else{
                voisin = courante->a->u; 
            }
            if(visite[voisin-1] == 0){
                visite[voisin-1] = 1;
                enfile(f,voisin);
                chemin[voisin-1] = chemin[val -1] +1; 
                predecesseur[voisin-1] = val;
            }
    
            courante = courante->suiv; 
        }

    }
    int tmp = v;
    Cell_entier *L = NULL;

    while(tmp != u){
        L = ajout_en_tete(L,tmp);
        printf("ajout de tmp=%d à la liste\n",tmp);
        tmp = predecesseur[tmp-1]; 
    }
    L = ajout_en_tete(L,u);
    liberer_file(f);
    return L; 
}
/*Cette fonction -crée le graphe correspondant au réseau.
                 -calcule la plus courte chaı̂ne pour chaque commodite.
                 -et qui retourne vrai si pour toute arête du graphe, le nombre de chaı̂nes qui passe par cette
                 arête est inférieur à γ, et faux sinon. On créera une matrice permettant de compter le nombre
                 de chaı̂nes passant par chaque arête {u, v}.*/
LC_commo* ajout_en_tete_commo(LC_commo *L, Cell_entier* Chaine,Commod com,int numéro){
    LC_commo *nouveau = (LC_commo*)malloc(sizeof(LC_commo)); 
    nouveau->num = numéro;
    nouveau->c = com;
    nouveau->chaine = Chaine;
    nouveau->suiv = L;
    return nouveau; 
}

int reorganiseReseau(Reseau* r){
    Graphe* g = creerGraphe(r);
    Commod* Tab_commodites = g->T_commod;
    int nb_commodites = g->nbcommod;
    
    LC_commo *lc_commo = NULL; 
    
    for(int i=0; i<nb_commodites;i++){
        Commod c = Tab_commodites[i];
        Cell_entier* chaine = arborescence_chemins(g,c.e1, c.e2); 
        lc_commo = ajout_en_tete_commo(lc_commo,chaine,c,i);
    }

    

}





























































/*Fonction qui libère la file*/
void liberer_file(S_file *f){
    while(!estFileVide(f)){
        defile(f);
    }
    free(f); 
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
        return;
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
    liberer_sommets(g->T_som,g->nbsom);
    free(g->T_commod);
    free(g); 
}