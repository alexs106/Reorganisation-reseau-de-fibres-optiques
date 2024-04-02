#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include <math.h>


/*Cette fonction permet de créer une table de hachage d'une taille M.*/
TableHachage* creation_table_hachage(int tailleM){
    TableHachage* t = malloc(sizeof(TableHachage));
    t->nbElement = 0;
    t->tailleMax = tailleM;
    t->T = malloc(sizeof(CellNoeud)*tailleM);
    for(int i=0;i<tailleM;i++){
        t->T[i] = NULL;
    }
    return t;
}

/*Cette fonction permet d'obtenir une clé avec les coordonnées x et y.*/
int cle(double x,double y){
    int res = (y+(x+y)*(x+y+1))/2;
    return res; 
}

/*Cette fonction permet d'obtenir clé hachée (l'indice de la clé dans la table de hachage)*/ 
int hachage(int k,TableHachage* h){
    int M = h->tailleMax;
    double A = (sqrt(5)-1)/2;
    int tmp = k*A; 
    return M * (k*A - tmp); 
}

/*Cette fonction retourne le noeud x et y s'il existe sinon la fonction le construit et l'ajoute dans la table de hachage*/
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y){
    //on initialise les éléments de la table de hachage
    int c = cle(x,y);
    int indice = hachage(c,H);

    CellNoeud* cell_n = H->T[indice]; //on récupère la liste CellNoeud à l'indice donné.
    
    while(cell_n != NULL){ //on parcourt alors cette liste
        Noeud* n = cell_n->nd; 
        if((n->x == x) && (n->y == y)){ //On regarde s'il y a un noeud qui a les mêmes coordonnées x y.
            return n; //On retourne le noeud
        }
        cell_n = cell_n->suiv;
    }
    R->nbNoeuds = R->nbNoeuds + 1;
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
    R->noeuds = ajout_noeud(R->noeuds, new_celln);
    
    return new_noeud;
}

/*Foction qui reconstruit le réseau à partir de la liste de chaînes C avec une table de hachage de taille M*/
Reseau* reconstitueReseauHachage(Chaines *C, int M){
    //Création du reseau.
    Reseau* reseau = creer_reseau();
    reseau->gamma = C->gamma;
    //Création de la table de hachage de taille M.
    TableHachage* TH = creation_table_hachage(M);

    //On recupère les chaines de la Chaine C
    CellChaine* liste = C->chaines;

    //On parcourt toutes les chaines
    while(liste){
        //On crée la commodité
        CellCommodite* commodite = creer_cell_commodite();
        
        CellPoint* liste_points = liste->points;  //liste des points dans la chaine
        CellPoint* precedant = liste_points, *suiv = NULL; //On garde le precedant et le suivant

        //Premier point, on le cherche et le rajoute s'il n'est pas dans le réseau
        Noeud* n = rechercheCreeNoeudHachage(reseau, TH, liste_points->x, liste_points->y); 

        commodite->extrA = n; 
        //On parcourt tous les CellPoints
        while(liste_points->suiv != NULL){
            suiv = liste_points->suiv; 
            Noeud* n = rechercheCreeNoeudHachage(reseau, TH, liste_points->x, liste_points->y);

            //Ajout des voisins au noeud n2
            ajouter_voisin(n,rechercheCreeNoeudHachage(reseau, TH, precedant->x, precedant->y));
            ajouter_voisin(n,rechercheCreeNoeudHachage(reseau, TH, suiv->x, suiv->y));

            //on passe au point suivant
            precedant = liste_points;
            liste_points = liste_points->suiv; 
        }

        commodite->extrB = rechercheCreeNoeudHachage(reseau,TH, liste_points->x, liste_points->y);
        //on rajoute le voisin précédant vu qu'on est dans l'extremité B
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudHachage(reseau, TH, precedant->x, precedant->y));

        //inserer la commodite au reseau
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite; 
        
        //On a rajoute la commodite et le noeud de la chaine au réseau, donc on passe à la chaine suivante

        liste = liste->suiv; 
    }
    liberation_hachage(TH); 
    //on retourne le reseau
    return reseau; 
}

//Libérer la table de hachage
void liberation_hachage(TableHachage* TableH){
    //liberer_CellNoeud(TableH->T);
    free(TableH->T); 
    free(TableH); 
}

