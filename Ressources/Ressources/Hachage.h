#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"

typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud** T;
}TableHachage;

int cle(double x,double y); 
int hachage(int k, TableHachage *h); 
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);

#endif