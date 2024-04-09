#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include <math.h>


/*Fonction qui détermine les coordonnées minimales et maximales 
des points des chaînes du réseau */
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
    CellChaine* chaines = C->chaines;
    CellPoint* points = chaines->points; 
    //On donne les valeurs du premier points au min et max
    *xmin = points->x;
    *xmax = points->x;
    *ymin = points->y;
    *ymax = points->y; 

    while(chaines != NULL){ //On parcourt les chaines
        points = chaines -> points;
        while(points){ //On parcourt les points
            //On vérifie si les premières valeurs stockées sont bien les min et max
            //Sinon, on les remplace
            if(points->x < *xmin) *xmin = points->x;
            if(points->x > *xmax) *xmax = points->x;
            if(points->y < *ymin) *ymin = points->y;
            if(points->y > *ymax) *ymax = points->y; 
            points = points->suiv; //modif Noah
        }
        chaines = chaines->suiv;
    }
}

/*Fonction qui crée un Arbre Quaternaire et initialise le noeud et les arbres à NULL*/
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
    ArbreQuat* aq = (ArbreQuat*)malloc(sizeof(ArbreQuat));
    aq->xc = xc;
    aq->yc = yc;
    aq->coteX = coteX;
    aq->coteY = coteY;

    aq->noeud = NULL;

    aq->no = NULL;
    aq->ne = NULL;
    aq->so = NULL;
    aq->se = NULL; 
    return aq; 
}

/*Fonction qui permet d'insérer un Noeud du réseau dans un arbre quaternaire*/
/*
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
    
    //Cas de l'arbre vide
    printf("Je passe ici 1\n");
    if(*a == NULL){
        double xc;
        double yc;
        
        //Trouver les coordonnées du centre

        //Si le x du noeud est plus petit que celui du parent
        //On se place à l'ouest (JE CROIS!) -> VERIFER 
        if(n->x < parent->xc){
            xc = parent->xc - (parent->coteX/4);
        }else{ //Sinon, on se place à l'est
            xc = parent->xc + (parent->coteX/4);
        }

        //Si le y du noeud est plus petit que celui du parent
        //On se place au sud
        if(n->y < parent->yc){
            yc = parent->yc - (parent->coteY/4);
        }else{ //Sinon, on se place au nord 
            yc = parent->yc + (parent->coteY/4); 
        }

        //Création de l'arbre quaternaire
        *a = creerArbreQuat(xc,yc,parent->coteX/2,parent->coteY/2);

        (*a)->noeud = n; 
        return ; //Il faut sortir du programme après la création 
    }

    else{
        //Cas de feuille
        if ((*a)->noeud != NULL){ 
            Noeud *tmp = (*a)->noeud;

            (*a)->noeud = NULL; //La feuille devient la cellule interne

            insererNoeudArbre(n,a,parent);
            insererNoeudArbre(tmp,a,parent);
        }

        //Cas de cellule interne
        //if ((*a != NULL) && ((*a)->noeud == NULL)){

            if(n->x < (*a)->xc){ //insertion du noeud à l'ouest
                if(n->y < (*a)->yc){ //
                    insererNoeudArbre(n, &((*a)->so),*a); //insertion du noeud dans le sous-arbre so
                }else{
                    insererNoeudArbre(n,&((*a)->no),*a); //insertion du noeud dans le sous-arbre no
                }
            }else{ //insertion du noeud à l'est 
                if(n->y < (*a)->yc){
                    insererNoeudArbre(n, &((*a)->se),*a); //insertion du noeud dans le sous-arbre se
                }else{
                    insererNoeudArbre(n, &((*a)->ne),*a); //insertion du noeud dans le sous-arbre ne
                }
            }
        //} 
        return;
    }
   
} 
*/

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){

    if(!*a){

        double xc , yc ;
        if(n->x < parent->xc){
            xc = parent->xc - (parent->coteX/4.0);
        }else{
            xc = parent->xc + (parent->coteX/4.0);
        }

        if(n->y < parent->yc){
            yc = parent->yc - (parent->coteY/4.0);
        }else{
            yc = parent->yc + (parent->coteY/4.0);
        }

        *a = creerArbreQuat(xc, yc, parent->coteX/2.0, parent->coteY/2.0); 
        
        (*a)->noeud = n;

        return;
    }

    if((*a)->noeud){

        Noeud *tmp = (*a)->noeud;
        
        (*a)->noeud = NULL;
        
        insererNoeudArbre(n, a, parent);

        insererNoeudArbre(tmp, a, parent);

        return;
    }

    
    if(n->x < (*a)->xc){ 

        if(n->y < (*a)->yc){
            insererNoeudArbre(n, &(*a)->so, *a);
        }else{
            insererNoeudArbre(n, &(*a)->no, *a);
        }

    }else{

        if(n->y < (*a)->yc){
            insererNoeudArbre(n, &(*a)->se, *a);
        }else{
            insererNoeudArbre(n, &(*a)->ne, *a);
        }

    }

}

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){

    if(!*a){
        printf("Je passe iciarbre vide\n");
       
        //Création du noeud 
        R->nbNoeuds = R->nbNoeuds + 1;
        Noeud* n = creer_noeud();
        n->x = x;
        n->y = y;
        n->num = R->nbNoeuds;
        n->voisins = NULL; 

        CellNoeud *cn = creer_cell_noeud();
        cn->nd = n;
        cn->suiv = NULL;

        R->noeuds = ajout_noeud(R->noeuds,cn);

        insererNoeudArbre(n, a, parent);
        return n;
    }
    
    if((*a)->noeud){
        printf("Je passe feuille\n");
        if((*a)->noeud->x == x && (*a)->noeud->y == y){
            return (*a)->noeud;
        }

        //Création du noeud 
        R->nbNoeuds = R->nbNoeuds + 1;
        Noeud* n = creer_noeud();
        n->x = x;
        n->y = y;
        n->num = R->nbNoeuds;
        n->voisins = NULL;

        CellNoeud *cn = creer_cell_noeud();
        cn->nd = n;
        cn->suiv = NULL; // inserer dans le reseau

        R->noeuds = ajout_noeud(R->noeuds, cn); 

        insererNoeudArbre(n, a, parent); //inserer dans le tableau

        return n;
    }

    //else (cas cellule interne)
    printf("Je passe ici cell interne\n");
    if(x < (*a)->xc){ //on determine dans quelle sous arbre on doit continuer

        if(y < (*a)->yc){
            return rechercheCreeNoeudArbre(R, &(*a)->so, *a, x, y);
        }else{
            return rechercheCreeNoeudArbre(R, &(*a)->no, *a, x, y);
        }

    }else{
        
        if(y < (*a)->yc){
            return rechercheCreeNoeudArbre(R, &(*a)->se, *a, x, y);
        }else{
            return rechercheCreeNoeudArbre(R, &(*a)->ne, *a, x, y);
        }

    }
}

/*Retourne un noeud du réseau correspondant au point dans l'arbre quaternaire
Si le noeud existe, la fonction retourne le noeud existant
sinon, on crée le noeud et on l'ajoute dans l'arbre et la liste des noeuds*/

/*
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){
    //Cas de l'arbre vide
    if(*a == NULL){
    
        //Création du noeud 
        R->nbNoeuds = R->nbNoeuds + 1;
        Noeud* new_noeud = creer_noeud();
        new_noeud->x = x;
        new_noeud->y = y;
        new_noeud->num = R->nbNoeuds;

        //Création du CellNoeud
        CellNoeud *cn = creer_cell_noeud();
        cn->nd = new_noeud; 
        cn->suiv = R->noeuds; //on insère dans le réseau

        R->noeuds = cn;
        R->nbNoeuds++;

        insererNoeudArbre(new_noeud,a,parent); //on insère dans le tableau
        return new_noeud;
    }
    else{
        
        //Cas de la feuille
        if((*a)->noeud != NULL){
            //si le noeud qu'on recherche 
            //correspond à celui de la feuille
            if((*a)->yc == x && (*a)->xc == y){
                return (*a)->noeud; 
            }
            else{//sinon, on crée le noeud correspondant 

            //Création du noeud 
            R->nbNoeuds = R->nbNoeuds + 1;
            Noeud* new_noeud = creer_noeud();
            new_noeud->x = x;
            new_noeud->y = y;
            new_noeud->num = R->nbNoeuds;

            //Création du CellNoeud
            CellNoeud *cn = creer_cell_noeud();
            cn->nd = new_noeud; 
            cn->suiv = R->noeuds; //on insère dans le réseau

            R->noeuds = cn;
            R->nbNoeuds++;
         
            insererNoeudArbre(new_noeud,a,parent); //on insère dans le tableau
            return new_noeud;
            }

        }

        //Cas de la cellule interne
        if((*a) != NULL && (*a)->noeud == NULL){
            if(x<(*a)->xc){ 
                if(y<(*a)->yc){
                    return rechercheCreeNoeudArbre(R, &(*a)->so, *a, x, y);
                }else{
                    return rechercheCreeNoeudArbre(R, &(*a)->no, *a, x, y);
                }
            }else{
                if(y<(*a)->yc){
                    return rechercheCreeNoeudArbre(R,&(*a)->se, *a, x, y); 
                }else{
                    return rechercheCreeNoeudArbre(R,&(*a)->ne, *a, x, y);
                }
            }
        }
        
        return NULL; 

    }
}

*/

/*Libération de mémoire de l'arbre quaternaire*/
void liberer_Arbre_Q(ArbreQuat* a){
    if(a){
        if(a->se){
            liberer_Arbre_Q(a->se);
        }
         if(a->so){
            liberer_Arbre_Q(a->so);
        }
         if(a->ne){
            liberer_Arbre_Q(a->ne);
        }
         if(a->no){
            liberer_Arbre_Q(a->no);
        }
    }
    free(a); 
}

Reseau* reconstitueReseauArbre(Chaines* C){
    
    //Initialisation de l'arbre quaternaire
    double xmin,xmax,ymin,ymax;
    chaineCoordMinMax(C,&xmin,&ymin,&xmax,&ymax);
    ArbreQuat* p = NULL;
    ArbreQuat* a = creerArbreQuat(xmin + ((xmax - xmin) / 2.0), ymin + ((ymax-ymin) / 2.0) ,xmax - xmin , ymax-ymin);
    
    //Création du réseau
    Reseau* reseau = creer_reseau();
    reseau->gamma = C->gamma;

    //On récupère la liste des chaines
    CellChaine* liste = C->chaines; 

    while(liste){
        //On crée la commodité
        CellCommodite* commodite = creer_cell_commodite();
        
        CellPoint* liste_points = liste->points;  //liste des points dans la chaine
        CellPoint* precedant = liste_points, *suiv = NULL; //On garde le precedant et le suivant

        //Premier point, on le cherche et le rajoute s'il n'est pas dans le réseau
        Noeud* n = rechercheCreeNoeudArbre(reseau,&a,p,liste_points->x,liste_points->y);
        commodite->extrA = n; 
        //On parcourt tous les CellPoints
        while(liste_points->suiv != NULL){
            suiv = liste_points->suiv; 
            Noeud* n = rechercheCreeNoeudArbre(reseau,&a,p, liste_points->x, liste_points->y);

            //Ajout des voisins au noeud n2
            ajouter_voisin(n,rechercheCreeNoeudArbre(reseau,&a,p,precedant->x,precedant->y));
            //rechercheCreeNoeudArbre(reseau,&a,p,precedant->x,precedant->y));
            ajouter_voisin(n,rechercheCreeNoeudArbre(reseau,&a,p, suiv->x, suiv->y));

            //on passe au point suivant
            precedant = liste_points;
            liste_points = liste_points->suiv; 
        }
        commodite->extrB = rechercheCreeNoeudArbre(reseau, &a, p, liste_points->x, liste_points->y);
        
        //on rajoute le voisin précédant vu qu'on est dans l'extremité B
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudArbre(reseau, &a, p, precedant->x, precedant->y));

        //inserer la commodite au reseau
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite; 
        
        //On a rajoute la commodite et le noeud de la chaine au réseau, donc on passe à la chaine suivante

        liste = liste->suiv; 
    }
    liberer_Arbre_Q(a); 
    return reseau; 
}






