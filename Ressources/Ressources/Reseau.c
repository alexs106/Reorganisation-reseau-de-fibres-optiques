#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include <math.h>
#include "SVGwriter.h"

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

CellNoeud* ajout_noeud(CellNoeud *tete, CellNoeud *elem){
    elem->suiv = tete;
    tete = elem;
    return tete; 
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

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud* cn = R->noeuds;
    while(cn!=NULL){
        Noeud* noe = cn -> nd;
        if(noe->x == x && noe->y == y){
            return noe;
        }
        cn = cn->suiv; 
    }

    R->nbNoeuds = R->nbNoeuds + 1;
    Noeud* new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds;
    new_noeud->voisins = NULL;

    CellNoeud* new_celln = creer_cell_noeud();
    new_celln->nd = new_noeud;
    new_celln->suiv = NULL; 

    R->noeuds = ajout_noeud(R->noeuds, new_celln);
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


int nbCommodites(Reseau *R){
    CellCommodite* cell_com = R->commodites;
    int nb = 0;
    while(cell_com != NULL){
        nb++;
        cell_com = cell_com->suiv;
    }
    return nb;
}

int nbLiaisons(Reseau *R){
    //on regarde tous les noeuds (la liste commence par 12 )
    //on regarde ses voisin, si ses voisins sont plus grands
    //que lui on le considère pas sinon on rajoute 1 à nb liason.

    CellNoeud* cell_n = R->noeuds;
    int nb_liaisons = 0;
    while(cell_n != NULL){
        Noeud* n = cell_n->nd;
        CellNoeud* voisins = n->voisins;

        while(voisins != NULL){
           
            if(n->num > voisins->nd->num){
                nb_liaisons++;
            }
            voisins = voisins->suiv;
        }
        cell_n = cell_n->suiv;
    }
    return nb_liaisons;
}


/*Exercice 3 - question n°2 */
void ecrireReseau(Reseau *R, FILE *f){
    if(f == NULL){
       printf("Erreur d'ouverture du fichier\n");
       exit(1);
    }
    int nb_noeuds = R->nbNoeuds;
    fprintf(f,"NbNoeuds: %d\n",nb_noeuds);

    int nb_liaisons = nbLiaisons(R);
    fprintf(f,"NbLiaisons: %d\n",nb_liaisons);

    int nb_com = nbCommodites(R);
    fprintf(f,"NbCommodites: %d\n",nb_com);

    int gamma = R->gamma;
    fprintf(f,"Gamma: %d\n",gamma);

    fprintf(f,"\n");

    //écriture des noeuds dans le fichier (ligne 6 à 17 voir énoncé).
    CellNoeud* cell_n = R->noeuds;

    while(cell_n != NULL){
        Noeud* n = cell_n->nd;
        fprintf(f,"v %d %.6f %.6f\n",n->num,n->x,n->y);
        cell_n = cell_n->suiv;
    }

    fprintf(f,"\n");

    //écriture des liaisons dans le fichier (ligne 19 à 33 voir énoncé).
    CellNoeud* cell_n_l = R->noeuds;
    while(cell_n_l != NULL){
        Noeud* n_l = cell_n_l->nd;
        CellNoeud* voisins = n_l->voisins;
        
        while(voisins != NULL){
            if(n_l->num > voisins->nd->num){
                fprintf(f,"l %d %d\n",voisins->nd->num,n_l->num);
            }
            voisins = voisins->suiv;
        }
        cell_n_l = cell_n_l->suiv;
    }

    fprintf(f,"\n");
    
    //écriture des commodités dans le fichier (ligne 35 à 42).
    CellCommodite *cell_c = R->commodites;
    while(cell_c != NULL){
        fprintf(f,"k %d %d\n",cell_c->extrA->num,cell_c->extrB->num);
        cell_c = cell_c->suiv;
    }

    fclose(f); //fermeture du fichier
}

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
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

